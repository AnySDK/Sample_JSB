
var analytics_plugin = null;

var Analytics = cc.Class.extend({
	ctor:function(){
		analytics_plugin = anysdk.AgentManager.getInstance().getAnalyticsPlugin();
	},
	startSession:function(){
		if (analytics_plugin) {
			analytics_plugin.startSession();
		}
	},
	stopSession:function(){
		if (analytics_plugin) {
			analytics_plugin.stopSession();
		}
	},
	logError:function(errID, errMsg){
		if (analytics_plugin) {
			analytics_plugin.logError(errID, errMsg);
		}
	},
	logEvent:function(eventID){
		if (analytics_plugin) {
			analytics_plugin.logEvent(eventID);
		}
	}
});