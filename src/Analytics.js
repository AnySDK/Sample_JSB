
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
				Account_Type : (AccountType.ANONYMOUS).toString(),
				Account_Level : "1",
				Account_Age : "1",
				Account_Operate : (AccountOperate.LOGIN).toString(),
				Account_Gender : (AccountGender.MALE).toString(),
				Server_Id : "1"
			}
			var data = anysdk.PluginParam.create(paramMap);
			analytics_plugin.callFuncWithParam("setAccount", data);
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
			var data = anysdk.PluginParam.create(paramMap);
			analytics_plugin.callFuncWithParam("onChargeRequest",data);
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
			var data = anysdk.PluginParam.create(paramMap);
			analytics_plugin.callFuncWithParam("onChargeOnlySuccess",data);
		}
	},
	onChargeSuccess:function(){
		if(analytics_plugin && analytics_plugin.isFunctionSupported("onChargeSuccess")){
			var data = anysdk.PluginParam.create("123456");
			analytics_plugin.callFuncWithParam("onChargeSuccess",data);
		}
	},
	onChargeFail:function(){
		if(analytics_plugin && analytics_plugin.isFunctionSupported("onChargeFail")){
			var paramMap = {
				Order_Id : "123456",
				Fail_Reason : "test"
			}
			var data = anysdk.PluginParam.create(paramMap);
			analytics_plugin.callFuncWithParam("onChargeFail",data);
		}
	},
	onPurchase:function(){
		if(analytics_plugin && analytics_plugin.isFunctionSupported("onPurchase")){
			var paramMap = {
				Item_Id : "123456",
				Item_Type : "test",
				Item_Count : "2",
				Vitural_Currency : "1",
				Currency_Type : agent.getChannelId()
			}
			var data = anysdk.PluginParam.create(paramMap);
			analytics_plugin.callFuncWithParam("onPurchase",data);
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
			var data = anysdk.PluginParam.create(paramMap);
			analytics_plugin.callFuncWithParam("onUse",data);	
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
			var data = anysdk.PluginParam.create(paramMap);
			analytics_plugin.callFuncWithParam("onReward",data);	
		}
	},
	startLevel:function(){
		if(analytics_plugin && analytics_plugin.isFunctionSupported("startLevel")){
			var paramMap = {
				Level_Id : "123456",
				Seq_Num : "1"
			}
			var data = anysdk.PluginParam.create(paramMap);
			analytics_plugin.callFuncWithParam("startLevel", data);
		}
	},
	finishLevel:function(){
		if(analytics_plugin && analytics_plugin.isFunctionSupported("finishLevel")){
			var data = anysdk.PluginParam.create("123456");
			analytics_plugin.callFuncWithParam("finishLevel",data);
		}
	},
	failLevel:function(){
		if(analytics_plugin && analytics_plugin.isFunctionSupported("failLevel")){
			var paramMap = {
				Level_Id : "123456",
				Fail_Reason : "test"
			}
			var data = anysdk.PluginParam.create(paramMap);
			analytics_plugin.callFuncWithParam("failLevel",data);
		}
	},
	startTask:function(){
		if(analytics_plugin && analytics_plugin.isFunctionSupported("startTask")){
			var paramMap  ={
				Task_Id : "123456",
				Task_Type : (TaskType.GUIDE_LINE).toString()
			}
			var data = anysdk.PluginParam.create(paramMap);
			analytics_plugin.callFuncWithParam("startTask",data);
		}
	},
	finishTask:function(){
		if(analytics_plugin && analytics_plugin.isFunctionSupported("finishTask")){
			var data = anysdk.PluginParam.create("123456");
			analytics_plugin.callFuncWithParam("finishTask",data);	
		}
	},
	failTask:function(){
		if(analytics_plugin && analytics_plugin.isFunctionSupported("failTask")){
			var paramMap = {
				Task_Id : "123456",
				Fail_Reason : "test"
			}		
			var data = anysdk.PluginParam.create(paramMap);
			analytics_plugin.callFuncWithParam("failTask",data);
		}
	}
});