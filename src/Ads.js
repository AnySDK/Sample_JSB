
var ads_plugin = null;

var Ads = cc.Class.extend({
	ctor:function(){
		ads_plugin = anysdk.AgentManager.getInstance().getAdsPlugin();
		if (ads_plugin) {
			ads_plugin.setAdsListener(this.onAdsResult, this);
		};
	},
	showAds:function(adType){
        if ( ads_plugin && ads_plugin.isAdTypeSupported(adType) )
            ads_plugin.showAds(adType);
	},
	hideAds:function(adType){
        if ( ads_plugin && ads_plugin.isAdTypeSupported(adType) )
            ads_plugin.hideAds(adType);
	},
	onAdsResult:function(code,msg){
		switch(code){
			case AdsResultCode.kAdsReceived:
				// do something.
				break;
		}
	}
});