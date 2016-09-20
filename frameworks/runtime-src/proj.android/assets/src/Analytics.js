
var analytics_plugin = null;

var Analytics = cc.Class.extend({
	ctor:function(){
		analytics_plugin = anysdk.agentManager.getAnalyticsPlugin();
	},
	startSession:function(){
		if (analytics_plugin) {
            var data = /*anysdk.PluginParam.create(*/{roleId:"123456",roleName:"test",roleLevel:"10",zoneId:"123",zoneName:"test",dataType:"1",ext:"login"}/*)*/;
            analytics_plugin.logEvent("onChargeRequest",data);
                                
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
	logEvent:function(eventID, paramMap){
		if (analytics_plugin) {
			if (paramMap == null) {
				analytics_plugin.logEvent(eventID);
			}else{
				analytics_plugin.logEvent(eventID, paramMap);
			}
		}
	},
	logTimedEventBegin:function(everntID){
		if (analytics_plugin) {
			analytics_plugin.logTimedEventBegin(everntID);
		}
	},
	logTimedEventEnd:function(everntID){
		if (analytics_plugin) {
			analytics_plugin.logTimedEventEnd(everntID);
		}
	},
	setAccount:function(){
		if(analytics_plugin && analytics_plugin.isFunctionSupported("setAccount")){
			 var paramMap = {
				Account_Id : "123456",
				Account_Name : "test",
				Account_Type : (anysdk.AccountType.ANONYMOUS).toString(),
				Account_Level : "1",
				Account_Age : "1",
				Account_Operate : (anysdk.AccountOperate.LOGIN).toString(),
				Account_Gender : (anysdk.AccountGender.MALE).toString(),
				Server_Id : "1"
			}
			analytics_plugin.setAccount(paramMap);
		}
	},
	onChargeRequest:function(){
		if(analytics_plugin && analytics_plugin.isFunctionSupported("onChargeRequest")){
			var paramMap = {
				Order_Id : "123456",
				Product_Name : "test",
				Currency_Amount : "2.0",
				Currency_Type : "CNY",
				Payment_Type : "渠道",
				Virtual_Currency_Amount : "100"
			}
			analytics_plugin.onChargeRequest(paramMap);
		}
	},
	onChargeOnlySuccess:function(){
		if(analytics_plugin && analytics_plugin.isFunctionSupported("onChargeOnlySuccess")){
			var paramMap = {
				Order_Id : "123456",
				Product_Name : "test",
				Currency_Amount : "2.0",
				Currency_Type : "1",
				Payment_Type : "1",
				Virtual_Currency_Amount : "100"
			}
			analytics_plugin.onChargeOnlySuccess(paramMap);
		}
	},
	onChargeSuccess:function(){
		if(analytics_plugin && analytics_plugin.isFunctionSupported("onChargeSuccess")){
			analytics_plugin.onChargeSuccess("123456");
		}
	},
	onChargeFail:function(){
		if(analytics_plugin && analytics_plugin.isFunctionSupported("onChargeFail")){
			var paramMap = {
				Order_Id : "123456",
				Fail_Reason : "test"
			}
			analytics_plugin.onChargeFail(paramMap);
		}
	},
	onPurchase:function(){
		if(analytics_plugin && analytics_plugin.isFunctionSupported("onPurchase")){
			var paramMap = {
				Item_Id : "123456",
				Item_Type : "test",
				Item_Count : "2",
				Virtual_Currency : "1",
				Currency_Type : agent.getChannelId()
			}
			analytics_plugin.onPurchase(paramMap);
		}
	},
	onUse:function(){
		if(analytics_plugin && analytics_plugin.isFunctionSupported("onUse")){
			var paramMap = {
				Item_Id : "123456",
				Item_Type : "test",
				Item_Count : "2",
				Use_Reason : "1"
		    }
			analytics_plugin.onUse(paramMap);
		}
	},
	onReward:function(){
		if(analytics_plugin && analytics_plugin.isFunctionSupported("onReward")){
			var paramMap = {
				Item_Id : "123456",
				Item_Type : "test",
				Item_Count : "2",
				Use_Reason : "1"
			}
			analytics_plugin.onReward(paramMap);
		}
	},
	startLevel:function(){
		if(analytics_plugin && analytics_plugin.isFunctionSupported("startLevel")){
			analytics_plugin.startLevel(paramMap);
		}
	},
	finishLevel:function(){
		if(analytics_plugin && analytics_plugin.isFunctionSupported("finishLevel")){
			analytics_plugin.finishLevel("123456");
		}
	},
	failLevel:function(){
		if(analytics_plugin && analytics_plugin.isFunctionSupported("failLevel")){
			var paramMap = {
				Level_Id : "123456",
				Fail_Reason : "test"
			}
			analytics_plugin.failLevel(paramMap);
		}
	},
	startTask:function(){
		if(analytics_plugin && analytics_plugin.isFunctionSupported("startTask")){
			var paramMap  ={
				Task_Id : "123456",
				Task_Type : (anysdk.TaskType.GUIDE_LINE).toString()
			}
			analytics_plugin.startTask(paramMap);
		}
	},
	finishTask:function(){
		if(analytics_plugin && analytics_plugin.isFunctionSupported("finishTask")){
			analytics_plugin.finishTask("123456");
		}
	},
	failTask:function(){
		if(analytics_plugin && analytics_plugin.isFunctionSupported("failTask")){
			var paramMap = {
				Task_Id : "123456",
				Fail_Reason : "test"
			}
			analytics_plugin.failTask(paramMap);
		}
	}
});