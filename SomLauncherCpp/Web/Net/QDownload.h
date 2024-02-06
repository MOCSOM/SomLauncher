#ifndef NET_QDOWNLOAD_H_
#define NET_QDOWNLOAD_H_

#include <QObject>

#include "../NetAction.h"
#include "HttpMetaCache.h"
#include "Validator.h"
#include "Sink.h"

namespace Net
{
	class Download : public NetAction
	{
		Q_OBJECT

	public: /* types */
		typedef shared_qobject_ptr<class Download> Ptr;
		enum class Option
		{
			NoOptions = 0,
			AcceptLocalFiles = 1
		};
		Q_DECLARE_FLAGS(Options, Option)

	protected: /* con/des */
		explicit Download();

	public:
		virtual ~Download() = default;
		static Download::Ptr makeCached(QUrl url, MetaEntryPtr entry, Options options = Option::NoOptions);
		static Download::Ptr makeByteArray(QUrl url, QByteArray* output, Options options = Option::NoOptions);
		static Download::Ptr makeFile(QUrl url, QString path, Options options = Option::NoOptions);

	public: /* methods */
		QString getTargetFilepath()
		{
			return m_target_path;
		}
		void addValidator(Validator* v);
		bool abort() override;
		bool canAbort() override;

	private: /* methods */
		bool handleRedirect();

	protected slots:
		void downloadProgress(qint64 bytesReceived, qint64 bytesTotal) override;
		void downloadError(QNetworkReply::NetworkError error) override;
		void sslErrors(const QList<QSslError>& errors) const;
		void downloadFinished() override;
		void downloadReadyRead() override;

	public slots:
		void startImpl() override;

	private: /* data */
		// FIXME: remove this, it has no business being here.
		QString m_target_path;
		std::unique_ptr<Sink> m_sink;
		Options m_options;
	};
}

Q_DECLARE_OPERATORS_FOR_FLAGS(Net::Download::Options)

#endif // !NET_QDOWNLOAD_H_