/*
* Streaming Adjuster
* Copyright (c) 2016 aap <aap@papnet.eu>
* Copyright (c) 2025 Adi <adriank3d@gmail.com>
* Licensed under the MIT License (http://opensource.org/licenses/MIT)
*/

#include "LimitAdjuster.h"
#include "OLACommon.h"


class StreamingInfo : public Adjuster
{
public:
	enum
	{
		ModelInfoPtrs,
		TxdStore,
	};
    
	static size_t modelInfoPtrs_t;
	static size_t infoForModel_t;
	static std::vector<char> modelInfoPtrs;
	static std::vector<char> aInfoForModel;

	static short NumDefaultModelInfoPtrs;
	static int NumDefaultTxdStore;
	static short NumModelInfoPtrs;
	static int NumTxdStore;

    StreamingInfo();
    virtual const Limit* GetLimits() override;
    virtual void ChangeLimit(int id, const std::string& value) override;
	virtual void Process() override;

	// convenience functions as the infoForModel patch relies on the other containers but they could be disabled in the ini
	static bool ShouldPatchModelInfoPtrs();
	static bool ShouldPatchTxdStore();
	static bool ShouldPatchInfoForModel();

	static void PatchStreamingIII();

} StreamingInfo;
