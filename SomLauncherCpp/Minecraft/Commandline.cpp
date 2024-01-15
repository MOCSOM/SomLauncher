#include "Commandline.h"

QStringList Commandline::splitArgs(QString args)
{
    QStringList argv;
    QString current;
    bool escape = false;
    QChar inquotes;
    for (int i = 0; i < args.length(); i++)
    {
        QChar cchar = args.at(i);

        // \ escaped
        if (escape)
        {
            current += cchar;
            escape = false;
            // in "quotes"
        }
        else if (!inquotes.isNull())
        {
            if (cchar == '\\')
                escape = true;
            else if (cchar == inquotes)
                inquotes = char(0);
            else
                current += cchar;
            // otherwise
        }
        else
        {
            if (cchar == ' ')
            {
                if (!current.isEmpty())
                {
                    argv << current;
                    current.clear();
                }
            }
            else if (cchar == '"' || cchar == '\'')
                inquotes = cchar;
            else
                current += cchar;
        }
    }
    if (!current.isEmpty())
        argv << current;
    return argv;
}

Commandline::ParsingError::ParsingError(const QString& what)
    : std::runtime_error(what.toStdString())
{
}

Commandline::Parser::Parser(FlagStyle::Enum flagStyle, ArgumentStyle::Enum argStyle)
    : m_flagStyle(flagStyle), m_argStyle(argStyle)
{
}

Commandline::Parser::~Parser()
{
    clear();
}

void Commandline::Parser::setFlagStyle(FlagStyle::Enum style)
{
    this->m_flagStyle = style;
}

Commandline::FlagStyle::Enum Commandline::Parser::flagStyle() const
{
    return this->m_flagStyle;
}

void Commandline::Parser::setArgumentStyle(ArgumentStyle::Enum style)
{
    this->m_argStyle = style;
}

Commandline::ArgumentStyle::Enum Commandline::Parser::argumentStyle() const
{
    return this->m_argStyle;
}

void Commandline::Parser::addSwitch(QString name, bool def)
{
    if (this->m_params.contains(name))
        throw "Name not unique";

    std::shared_ptr<OptionDef> param = std::make_shared<OptionDef>();
    param->type = otSwitch;
    param->name = name;
    param->metavar = QString("<%1>").arg(name);
    param->def = def;

    this->m_options[name] = param.get();
    this->m_params[name] = (CommonDef*)param.get();
    this->m_optionList.append(param.get());
}

void Commandline::Parser::addOption(QString name, QVariant def)
{
    if (m_params.contains(name))
        throw "Name not unique";

    std::shared_ptr<OptionDef> param = std::make_shared<OptionDef>();
    param->type = otOption;
    param->name = name;
    param->metavar = QString("<%1>").arg(name);
    param->def = def;

    this->m_options[name] = param.get();
    this->m_params[name] = (CommonDef*)param.get();
    this->m_optionList.append(param.get());
}

void Commandline::Parser::addArgument(QString name, bool required, QVariant def)
{
    if (m_params.contains(name))
        throw "Name not unique";

    std::shared_ptr<PositionalDef> param = std::make_shared<PositionalDef>();
    param->name = name;
    param->def = def;
    param->required = required;
    param->metavar = name;

    this->m_positionals.append(param.get());
    this->m_params[name] = (CommonDef*)param.get();
}

void Commandline::Parser::addShortOpt(QString name, QChar flag)
{
    if (!m_params.contains(name))
        throw "Name does not exist";
    if (!m_options.contains(name))
        throw "Name is not an Option or Swtich";

    OptionDef* param = m_options[name];
    this->m_flags[flag] = param;
    param->flag = flag;
}

void Commandline::Parser::addDocumentation(QString name, QString doc, QString metavar)
{
    if (!m_params.contains(name))
        throw "Name does not exist";

    CommonDef* param = m_params[name];
    param->doc = doc;
    if (!metavar.isNull())
        param->metavar = metavar;
}

QString Commandline::Parser::compileHelp(QString progName, int helpIndent, bool flagsInUsage)
{
    QStringList help;
    help << compileUsage(progName, flagsInUsage) << "\r\n";

    // positionals
    if (!this->m_positionals.isEmpty())
    {
        help << "\r\n";
        help << "Positional arguments:\r\n";
        QListIterator<PositionalDef*> it2(m_positionals);
        while (it2.hasNext())
        {
            PositionalDef* param = it2.next();
            help << "  " << param->metavar;
            help << " " << QString(helpIndent - param->metavar.length() - 1, ' ');
            help << param->doc << "\r\n";
        }
    }

    // Options
    if (!this->m_optionList.isEmpty())
    {
        help << "\r\n";
        QString optPrefix, flagPrefix;
        getPrefix(optPrefix, flagPrefix);

        help << "Options & Switches:\r\n";
        QListIterator<OptionDef*> it(this->m_optionList);
        while (it.hasNext())
        {
            OptionDef* option = it.next();
            help << "  ";
            int nameLength = optPrefix.length() + option->name.length();
            if (!option->flag.isNull())
            {
                nameLength += 3 + flagPrefix.length();
                help << flagPrefix << option->flag << ", ";
            }
            help << optPrefix << option->name;
            if (option->type == otOption)
            {
                QString arg = QString("%1%2").arg(
                    ((this->m_argStyle == ArgumentStyle::Equals) ? "=" : " "), option->metavar);
                nameLength += arg.length();
                help << arg;
            }
            help << " " << QString(helpIndent - nameLength - 1, ' ');
            help << option->doc << "\r\n";
        }
    }

    return help.join("");
}

QString Commandline::Parser::compileUsage(QString progName, bool useFlags)
{
    QStringList usage;
    usage << "Usage: " << progName;

    QString optPrefix, flagPrefix;
    getPrefix(optPrefix, flagPrefix);

    // options
    QListIterator<OptionDef*> it(this->m_optionList);
    while (it.hasNext())
    {
        OptionDef* option = it.next();
        usage << " [";
        if (!option->flag.isNull() && useFlags)
            usage << flagPrefix << option->flag;
        else
            usage << optPrefix << option->name;
        if (option->type == otOption)
            usage << ((this->m_argStyle == ArgumentStyle::Equals) ? "=" : " ") << option->metavar;
        usage << "]";
    }

    // arguments
    QListIterator<PositionalDef*> it2(this->m_positionals);
    while (it2.hasNext())
    {
        PositionalDef* param = it2.next();
        usage << " " << (param->required ? "<" : "[");
        usage << param->metavar;
        usage << (param->required ? ">" : "]");
    }

    return usage.join("");
}

QHash<QString, QVariant> Commandline::Parser::parse(QStringList argv)
{
    QHash<QString, QVariant> map;

    QStringListIterator it(argv);
    QString programName = it.next();

    QString optionPrefix;
    QString flagPrefix;
    QListIterator<PositionalDef*> positionals(this->m_positionals);
    QStringList expecting;

    getPrefix(optionPrefix, flagPrefix);

    while (it.hasNext())
    {
        QString arg = it.next();

        if (!expecting.isEmpty())
            // we were expecting an argument
        {
            QString name = expecting.first();
            /*
                        if (map.contains(name))
                            throw ParsingError(
                                QString("Option %2%1 was given multiple times").arg(name, optionPrefix));
            */
            map[name] = QVariant(arg);

            expecting.removeFirst();
            continue;
        }

        if (arg.startsWith(optionPrefix))
            // we have an option
        {
            // qDebug("Found option %s", qPrintable(arg));

            QString name = arg.mid(optionPrefix.length());
            QString equals;

            if ((m_argStyle == ArgumentStyle::Equals ||
                m_argStyle == ArgumentStyle::SpaceAndEquals) &&
                name.contains("="))
            {
                int i = name.indexOf("=");
                equals = name.mid(static_cast<qsizetype>(i) + 1);
                name = name.left(i);
            }

            if (m_options.contains(name))
            {
                /*
                if (map.contains(name))
                    throw ParsingError(QString("Option %2%1 was given multiple times")
                                           .arg(name, optionPrefix));
*/
                OptionDef* option = this->m_options[name];
                if (option->type == otSwitch)
                    map[name] = true;
                else // if (option->type == otOption)
                {
                    if (this->m_argStyle == ArgumentStyle::Space)
                        expecting.append(name);
                    else if (!equals.isNull())
                        map[name] = equals;
                    else if (this->m_argStyle == ArgumentStyle::SpaceAndEquals)
                        expecting.append(name);
                    else
                        throw ParsingError(QString("Option %2%1 reqires an argument.")
                            .arg(name, optionPrefix));
                }

                continue;
            }

            throw ParsingError(QString("Unknown Option %2%1").arg(name, optionPrefix));
        }

        if (arg.startsWith(flagPrefix))
            // we have (a) flag(s)
        {
            // qDebug("Found flags %s", qPrintable(arg));

            QString flags = arg.mid(flagPrefix.length());
            QString equals;

            if ((this->m_argStyle == ArgumentStyle::Equals ||
                this->m_argStyle == ArgumentStyle::SpaceAndEquals) &&
                flags.contains("="))
            {
                int i = flags.indexOf("=");
                equals = flags.mid(static_cast<qsizetype>(i) + 1);
                flags = flags.left(i);
            }

            for (int i = 0; i < flags.length(); i++)
            {
                QChar flag = flags.at(i);

                if (!m_flags.contains(flag))
                    throw ParsingError(QString("Unknown flag %2%1").arg(flag, flagPrefix));

                OptionDef* option = this->m_flags[flag];
                /*
                                if (map.contains(option->name))
                                    throw ParsingError(QString("Option %2%1 was given multiple times")
                                                           .arg(option->name, optionPrefix));
                */
                if (option->type == otSwitch)
                    map[option->name] = true;
                else // if (option->type == otOption)
                {
                    if (this->m_argStyle == ArgumentStyle::Space)
                        expecting.append(option->name);
                    else if (!equals.isNull())
                        if (i == flags.length() - 1)
                            map[option->name] = equals;
                        else
                            throw ParsingError(QString("Flag %4%2 of Argument-requiring Option "
                                "%1 not last flag in %4%3")
                                .arg(option->name, flag, flags, flagPrefix));
                    else if (this->m_argStyle == ArgumentStyle::SpaceAndEquals)
                        expecting.append(option->name);
                    else
                        throw ParsingError(QString("Option %1 reqires an argument. (flag %3%2)")
                            .arg(option->name, flag, flagPrefix));
                }
            }

            continue;
        }

        // must be a positional argument
        if (!positionals.hasNext())
            throw ParsingError(QString("Don't know what to do with '%1'").arg(arg));

        PositionalDef* param = positionals.next();

        map[param->name] = arg;
    }

    // check if we're missing something
    if (!expecting.isEmpty())
        throw ParsingError(QString("Was still expecting arguments for %2%1").arg(
            expecting.join(QString(", ") + optionPrefix), optionPrefix));

    while (positionals.hasNext())
    {
        PositionalDef* param = positionals.next();
        if (param->required)
            throw ParsingError(
                QString("Missing required positional argument '%1'").arg(param->name));
        else
            map[param->name] = param->def;
    }

    // fill out gaps
    QListIterator<OptionDef*> iter(m_optionList);
    while (iter.hasNext())
    {
        OptionDef* option = iter.next();
        if (!map.contains(option->name))
            map[option->name] = option->def;
    }

    return map;
}

inline void Commandline::Parser::clear()
{
    this->m_flags.clear();
    this->m_params.clear();
    this->m_options.clear();

    QMutableListIterator<OptionDef*> it(this->m_optionList);
    while (it.hasNext())
    {
        //OptionDef* option = it.next();
        it.remove();
        //delete option;
    }

    QMutableListIterator<PositionalDef*> it2(this->m_positionals);
    while (it2.hasNext())
    {
        //PositionalDef* arg = it2.next();
        it2.remove();
        //delete arg;
    }
}

void Commandline::Parser::getPrefix(QString& opt, QString& flag)
{
    if (this->m_flagStyle == FlagStyle::Windows)
        opt = flag = "/";
    else if (this->m_flagStyle == FlagStyle::Unix)
        opt = flag = "-";
    // else if (m_flagStyle == FlagStyle::GNU)
    else
    {
        opt = "--";
        flag = "-";
    }
}