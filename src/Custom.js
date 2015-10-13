

var custom_plugin = null;

var Custom = cc.Class.extend({
	ctor:function(){
		custom_plugin = anysdk.AgentManager.getInstance().getCustomPlugin();
        // set share result listener
        if (custom_plugin)
            custom_plugin.setResultListener(this.onCustomResult, this);
	},
    onCustomResult:function(code, msg){
        cc.log("custom result, resultcode:"+code+", msg: "+msg);
    }
});
