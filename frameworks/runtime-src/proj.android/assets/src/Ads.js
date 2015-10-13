
var ads_plugin = null;

var Ads = cc.Class.extend({
	ctor:function(){
		ads_plugin = anysdk.AgentManager.getInstance().getAdsPlugin();
		if (ads_plugin) {
			ads_plugin.setAdsListener(this.onActionResult, this);
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
	onActionResult:function(param1, param2){
		if ( typeof(param1) == "number" ){
		     this.onAdsResult(param1, param2);
		}else{
		     this.onPlayerGetPoints(param1, param2);
		}
	},
	onPlayerGetPoints:function(plugin, points){
		cc.log("on ads player get points listener.")
    	cc.log("points:"+points)
	},
	onAdsResult:function(code, msg){
		cc.log("on ads result listener.")
		cc.log("code:"+code+",msg:"+msg)
		switch(code)
		{
		case AdsResultCode.kAdsReceived:
	        //do
			break;
	    case AdsResultCode.kAdsShown:
	        //do
	    	break;
	    case AdsResultCode.kAdsDismissed:
	        //do
	    	break;
	    case AdsResultCode.kPointsSpendSucceed:
	        //do
	    	break;
	    case AdsResultCode.kPointsSpendFailed:
	        //do
	    	break;
	    case AdsResultCode.kNetworkError:
	        //do
	    	break;
	    case AdsResultCode.kUnknownError:
	        //do
	    	break;
	    case AdsResultCode.kOfferWallOnPointsChanged:
	        //do
	    	break;
	    default:
	    	break;
		}
	}
});