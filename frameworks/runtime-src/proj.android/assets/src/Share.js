
var share_plugin = null;

var Share = cc.Class.extend({
	ctor:function(){
		share_plugin = anysdk.agentManager.getSharePlugin();
        // set share result listener
        if (share_plugin)
            share_plugin.setListener(this.onShareResult, this);
	},
	share:function(adType){
        if ( share_plugin ){
            var info = {
                title : "ShareSDK是一个神奇的SDK",
                titleUrl : "http://sharesdk.cn",
                site : "ShareSDK",
                siteUrl : "http://sharesdk.cn",
                text : "ShareSDK集成了简单、支持如微信、新浪微博、腾讯微博等社交平台",
                comment : "无",
            };
            cc.log("share info:"+info+", "+info["site"]);
            share_plugin.share(info);
        }
	},
    onShareResult:function(code, msg){
        cc.log("on ads result listener.")
        cc.log("code:"+code+",msg:"+msg)
        switch(code)
        {
            case anysdk.ShareResultCode.kShareSuccess:
                //do
                break;
            case anysdk.ShareResultCode.kShareFail:
                //do
                break;
            case anysdk.ShareResultCode.kShareCancel:
                //do
                break;
            case anysdk.ShareResultCode.kShareNetworkError:
                //do
                break;         
            default:
                break;
        }
    }
});
