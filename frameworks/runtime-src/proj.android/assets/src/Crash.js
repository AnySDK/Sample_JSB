
var crash_plugin = null;

var Crash = cc.Class.extend({
	ctor:function(){
		crash_plugin = anysdk.agentManager.getCrashPlugin();
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