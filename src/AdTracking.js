
var adtracking_plugin = null;

var AdTracking = cc.Class.extend({
	ctor:function(){
		adtracking_plugin = anysdk.agentManager.getAdTrackingPlugin();
	},
	onRegister:function(){
        if (!adtracking_plugin) return;
		adtracking_plugin.onRegister("userid");

	},
	onLogin:function(){
        if (!adtracking_plugin) return;
        var info = {
        	"User_Id": "123456",
        	"Role_Id": "test",
        	"Role_Name": "test"
        };
		adtracking_plugin.onLogin(info);

	},
	onPay:function(){
        if (!adtracking_plugin) return;
        var myDate = new Date();
		var info = {
        	"User_Id": "123456",
        	"Order_Id": myDate.toLocaleTimeString(),
        	"Currency_Amount": "5",
        	"Currency_Type": "CNY",
        	"Payment_Type": "test",
        	"Payment_Time": myDate.toLocaleTimeString()
        };
		adtracking_plugin.onPay(info);

	},
	trackEvent:function(){
        if (!adtracking_plugin) return;
		adtracking_plugin.trackEvent("event_1");
		adtracking_plugin.trackEvent("event_2");

		adtracking_plugin.trackEvent("onCustEvent1");
		adtracking_plugin.trackEvent("onCustEvent2");


	},
	onCreateRole:function(){
        if (!adtracking_plugin || !this.isFunctionSupported("onCreateRole")) return;
		var info = {
        	"User_Id": "123456",
        	"Role_Id": "test",
        	"Role_Name": "test"
        };
		adtracking_plugin.trackEvent("onCreateRole", info);

	},
	onLevelUp:function(){
        if (!adtracking_plugin || !this.isFunctionSupported("onLevelUp")) return;
        var info = {
        	"User_Id": "123456",
        	"Role_Id": "test",
        	"Role_Name": "test",
        	"Level": "10"
        };
		adtracking_plugin.trackEvent("onLevelUp", info);

	},
	onStartToPay:function(){
        if (!adtracking_plugin || !this.isFunctionSupported("onStartToPay")) return;
        var myDate = new Date();
		var info = {
        	"User_Id": "123456",
        	"Order_Id": myDate.toLocaleTimeString(),
        	"Currency_Amount": "5",
        	"Currency_Type": "CNY",
        	"Payment_Type": "test",
        	"Payment_Time": myDate.toLocaleTimeString()
        };
		adtracking_plugin.trackEvent("onStartToPay", info);

	},
	isFunctionSupported:function(functionName){
		if (!adtracking_plugin) return false;
		return adtracking_plugin.isFunctionSupported(functionName);
	}
});