
var push_plugin = null;

var Push = cc.Class.extend({
	ctor:function(){
		push_plugin = anysdk.agentManager.getPushPlugin();
        // set share result listener
        if (push_plugin)
            push_plugin.setListener(this.onPushResult, this);
	},
	closePush:function(){
		push_plugin.closePush();
	},
	startPush:function(){
		push_plugin.startPush();
	},
	setAlias:function(){
        push_plugin.setAlias("ivenKill");
    },
	delAlias:function(){
		push_plugin.delAlias("ivenKill");
    },
    setTags:function(){
    	push_plugin.setTags(["easy","fast","qwe"]);
    },
    delTags:function(){
    	push_plugin.delTags(["easy","qwe"]);
    },
    onPushResult:function(code,msg){
		switch(code)
	    {
	    	case anysdk.PushActionResultCode.kPushReceiveMessage:
	    		//do
	    		break;
	    	default:
	    		break;
	    };
    }
});