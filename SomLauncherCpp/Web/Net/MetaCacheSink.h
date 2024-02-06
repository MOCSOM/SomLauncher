#ifndef NET_METACACHESINK_H_
#define NET_METACACHESINK_H_

#include "FileSink.h"
#include "ChecksumValidator.h"
#include "HttpMetaCache.h"

namespace Net
{
	class MetaCacheSink : public FileSink
	{
	public: /* con/des */
		MetaCacheSink(MetaEntryPtr entry, ChecksumValidator* md5sum);
		virtual ~MetaCacheSink();
		bool hasLocalData() override;

	protected: /* methods */
		JobStatus initCache(QNetworkRequest& request) override;
		JobStatus finalizeCache(QNetworkReply& reply) override;

	private: /* data */
		MetaEntryPtr m_entry;
		ChecksumValidator* m_md5Node;
	};
}

#endif // !NET_METACACHESINK_H_
