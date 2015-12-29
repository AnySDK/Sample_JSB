

var rec_plugin = null;

var REC = cc.Class.extend({
	ctor:function(){
		rec_plugin = anysdk.agentManager.getRECPlugin();
        // set rec result listener
        if (rec_plugin)
            rec_plugin.setListener(this.onRECResult, this);
	},
    startRecording:function(){
        if (rec_plugin) {
            rec_plugin.startRecording();
        }
    },
    stopRecording:function(){
        if (rec_plugin) {
            rec_plugin.stopRecording();
        }
    },
	share:function(adType){
        if ( rec_plugin ){
            var info = {
                Video_Title : "RECSDK",
                Video_Desc:"RECSDK是一个神奇的SDK"
            };
            rec_plugin.share(info);
        }
	},
    pauseRecording:function(){
        if (rec_plugin) {
            rec_plugin.pauseRecording();
        }
    },
    resumeRecording:function(){
        if (rec_plugin) {
            rec_plugin.resumeRecording();
        }
    },
    isAvailable:function(){
        if (rec_plugin) {
           return rec_plugin.isAvailable();
        }
    },
    showToolBar:function(){
        if (rec_plugin) {
            rec_plugin.showToolBar();
        }
    },
    hideToolBar:function(){
        if (rec_plugin) {
            rec_plugin.hideToolBar();
        }
    },
    isRecording:function(){
        if (rec_plugin) {
           return rec_plugin.isRecording();
        }
    },
    showVideoCenter:function(){
        if (rec_plugin) {
            rec_plugin.showVideoCenter();
        }
    },
    enterPlatform:function(){
        if (rec_plugin) {
            rec_plugin.enterPlatform();
        }
    },
    setMetaData:function(){
        if (rec_plugin) {
            var data = {ext:"login"};
            rec_plugin.setMetaData(data);
        }
    },

    onRECResult:function(code, msg){
        switch(code)
        {
        case anysdk.RECResultCode.kRECInitSuccess://初始化成功
            cc.log("kRECInitSuccess\n");
            break;
        case anysdk.RECResultCode.kRECInitFail://初始化失败
            cc.log("kRECInitFail\n");
            break;
        case anysdk.RECResultCode.kRECStartRecording://开始录制
            cc.log("kRECStartRecording \n");
            break;
        case anysdk.RECResultCode.kRECStopRecording://结束录制
            cc.log("kRECStopRecording \n");
            break;
        case anysdk.RECResultCode.kRECPauseRecording://暂停录制
            cc.log("kRECPauseRecording \n");
            break;
        case anysdk.RECResultCode.kRECResumeRecording://恢复录制
            cc.log("kRECResumeRecording \n");
            break;
        case anysdk.RECResultCode.kRECEnterSDKPage://进入SDK页面
            cc.log("kRECEnterSDKPage \n");
            break;
        case anysdk.RECResultCode.kRECQuitSDKPage://退出SDK页面
            cc.log("kRECQuitSDKPage \n");
            break;
        case anysdk.RECResultCode.kRECShareSuccess://视频分享成功
            cc.log("kRECShareSuccess \n");
            break;
        case anysdk.RECResultCode.kRECShareFail://视频分享失败
            cc.log("kRECShareFail \n");
            break;
        default:
            break;
        }
    }
});
