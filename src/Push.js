
var push_plugin = null;

var Push = cc.Class.extend({
	ctor:function(){
		push_plugin = anysdk.AgentManager.getInstance().getPushPlugin();
        // set share result listener
        if (push_plugin)
            push_plugin.setActionListener(this.onActionResult, this);
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
    onActionResult:function(plugin,code,msg){
		switch(code)
	    {
	    	case PushActionResultCode.kPushReceiveMessage:
	    		//do something;
	    		break;
	    	default:
	    		break;
	    };
    }
});