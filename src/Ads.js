
var ads_plugin = null;

var Ads = cc.Class.extend({
	ctor:function(){
		ads_plugin = anysdk.agentManager.getAdsPlugin();
		if (ads_plugin) {
			ads_plugin.setListener(this.onAdsResult, this);
		};
	},
	preloadAds:function(adType){
        if ( ads_plugin && ads_plugin.isAdTypeSupported(adType) )
            ads_plugin.preloadAds(adType);
	},
	showAds:function(adType){
        if ( ads_plugin && ads_plugin.isAdTypeSupported(adType) )
            ads_plugin.showAds(adType);
	},
	hideAds:function(adType){
        if ( ads_plugin && ads_plugin.isAdTypeSupported(adType) )
            ads_plugin.hideAds(adType);
	},
	queryPoints:function(){
		if ( ads_plugin )
			cc.log("points:"+ads_plugin.queryPoints());
	},
	spendPoints:function(points){
		if ( ads_plugin )
			ads_plugin.spendPoints(points);
	},
	onAdsResult:function(code, msg){
		cc.log("on ads result listener.")
		cc.log("code:"+code+",msg:"+msg)
		switch(code)
		{
		case anysdk.AdsResultCode.kAdsReceived:
	        //do
			break;
	    case anysdk.AdsResultCode.kAdsShown:
	        //do
	    	break;
	    case anysdk.AdsResultCode.kAdsDismissed:
	        //do
	    	break;
	    case anysdk.AdsResultCode.kPointsSpendSucceed:
	        //do
	    	break;
	    case anysdk.AdsResultCode.kPointsSpendFailed:
	        //do
	    	break;
	    case anysdk.AdsResultCode.kNetworkError:
	        //do
	    	break;
	    case anysdk.AdsResultCode.kUnknownError:
	        //do
	    	break;
	    case anysdk.AdsResultCode.kOfferWallOnPointsChanged:
	        //do
	    	break;
	    default:
	    	break;
		}
	}
});