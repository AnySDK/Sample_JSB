

var rec_plugin = null;

var REC = cc.Class.extend({
	ctor:function(){
		rec_plugin = anysdk.AgentManager.getInstance().getRECPlugin();
        // set rec result listener
        if (rec_plugin)
            rec_plugin.setResultListener(this.onRECResult, this);
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
            rec_plugin.callFuncWithParam("pauseRecording");
        }
    },
    resumeRecording:function(){
        if (rec_plugin) {
            rec_plugin.callFuncWithParam("resumeRecording");
        }
    },
    isAvailable:function(){
        if (rec_plugin) {
           return rec_plugin.callBoolFuncWithParam("isAvailable");
        }
    },
    showToolBar:function(){
        if (rec_plugin) {
            rec_plugin.callFuncWithParam("showToolBar");
        }
    },
    hideToolBar:function(){
        if (rec_plugin) {
            rec_plugin.callFuncWithParam("hideToolBar");
        }
    },
    isRecording:function(){
        if (rec_plugin) {
           return rec_plugin.callBoolFuncWithParam("isRecording");
        }
    },
    showVideoCenter:function(){
        if (rec_plugin) {
            rec_plugin.callFuncWithParam("showVideoCenter");
        }
    },
    enterPlatform:function(){
        if (rec_plugin) {
            rec_plugin.callFuncWithParam("enterPlatform");
        }
    },
    setMetaData:function(){
        if (rec_plugin) {
            var data = anysdk.PluginParam.create({ext:"login"});
            rec_plugin.callFuncWithParam("setMetaData", data);
        }
    },

    onRECResult:function(code, msg){
        switch(code)
        {
        case RECResultCode.kRECInitSuccess://初始化成功
            cc.log("kRECInitSuccess\n");
            break;
        case RECResultCode.kRECInitFail://初始化失败
            cc.log("kRECInitFail\n");
            break;
        case RECResultCode.kRECStartRecording://开始录制
            cc.log("kRECStartRecording \n");
            break;
        case RECResultCode.kRECStopRecording://结束录制
            cc.log("kRECStopRecording \n");
            break;
        case RECResultCode.kRECPauseRecording://暂停录制
            cc.log("kRECPauseRecording \n");
            break;
        case RECResultCode.kRECResumeRecording://恢复录制
            cc.log("kRECResumeRecording \n");
            break;
        case RECResultCode.kRECEnterSDKPage://进入SDK页面
            cc.log("kRECEnterSDKPage \n");
            break;
        case RECResultCode.kRECQuitSDKPage://退出SDK页面
            cc.log("kRECQuitSDKPage \n");
            break;
        case RECResultCode.kRECShareSuccess://视频分享成功
            cc.log("kRECShareSuccess \n");
            break;
        case RECResultCode.kRECShareFail://视频分享失败
            cc.log("kRECShareFail \n");
            break;
        default:
            break;
        }
    }
});
