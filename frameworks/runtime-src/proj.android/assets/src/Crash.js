
var crash_plugin = null;

var Crash = cc.Class.extend({
	ctor:function(){
		crash_plugin = anysdk.AgentManager.getInstance().getCrashPlugin();
	},
	setUserIdentifier:function(){
		if (crash_plugin) {
            crash_plugin.setUserIdentifier("AnySDK");
                                
		}
	},
	reportException:function(errID, errMsg){
		if (crash_plugin) {
			crash_plugin.reportException(errID, errMsg);
		}
	},
	leaveBreadcrumb:function(eventID){
		if (crash_plugin) {
			crash_plugin.leaveBreadcrumb(eventID);
		}
	}
});