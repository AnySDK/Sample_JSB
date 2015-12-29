

//注意：这里appKey, appSecret, privateKey，要替换成自己打包工具里面的值(登录打包工具，游戏管理界面上显示的那三个参数)
var appKey = "0914CB16-BAEE-790E-808E-3A37B8FFBE3F";
var appSecret = "62bee0ddb86bdeccb8acd959765041cc";
var privateKey = "96C273AB03E1A798BA1AD0C38004871F";
var oauthLoginServer = "http://oauth.anysdk.com/api/OauthLoginDemo/Login.php";

var agent = null;
var user_plugin = null;
var iap_plugin = null;
var analytics_plugin = null;

var PluginChannel = cc.Class.extend({
	loadPlugins:function(){
        agent = anysdk.agentManager;
        // init
        agent.init(appKey,appSecret,privateKey,oauthLoginServer);
        //cc.log("getChannelId"+ agent.getChannelId());
        //cc.log("getFrameworkVersion"+ agent.getFrameworkVersion());
        // load
        agent.loadAllPlugins();
        // get plugins
        user_plugin   = agent.getUserPlugin();
        var iapPlugins = anysdk.agentManager.getIAPPlugins();
        iap_plugin = agent.getIAPPlugin();
        analytics_plugin = agent.getAnalyticsPlugin();
        //cc.log("");
        if (user_plugin) {
        	user_plugin.setListener(this.onActionResult, this);
        }

        if(analytics_plugin){
            analytics_plugin.startSession();
            var data = {roleId:"123456",roleName:"test",roleLevel:"10",zoneId:"123",zoneName:"test",dataType:"1",ext:"login"};
            analytics_plugin.setAccount(data);
        }
        this.funcOfAgent();
	},
    funcOfAgent:function(){
        var customParam = agent.getCustomParam();
        cc.log("customParam:"+customParam);
        var channelId = agent.getChannelId();
        cc.log("channelId:"+channelId);
    },
    login:function(){
    	user_plugin.login();
    },
    logout:function(){
    	if ( user_plugin.isFunctionSupported("logout") )
    		user_plugin.logout();
    },
    enterPlatform:function(){
    	if ( user_plugin.isFunctionSupported("enterPlatform") )
    		user_plugin.enterPlatform();
    },
    showToolbar:function(pos){
        if ( user_plugin.isFunctionSupported("showToolBar") ){
            user_plugin.showToolBar(pos);
        }
    },
    hideToolbar:function(){
        if ( user_plugin.isFunctionSupported("hideToolBar") )
            user_plugin.hideToolBar();
    },
    accountSwitch:function(){
        if ( user_plugin.isFunctionSupported("accountSwitch") )
            user_plugin.accountSwitch();
    },
    realNameRegister:function(){
        if ( user_plugin.isFunctionSupported("realNameRegister") )
            user_plugin.realNameRegister();
    },
    antiAddictionQuery:function(){
        if ( user_plugin.isFunctionSupported("antiAddictionQuery") )
            user_plugin.antiAddictionQuery();
    },
    submitLoginGameRole:function(){
        if( user_plugin.isFunctionSupported("submitLoginGameRole") ){
            var data = {roleId:"123456",roleName:"test",roleLevel:"10",zoneId:"123",zoneName:"test",dataType:"1",ext:"login"};
            user_plugin.submitLoginGameRole(data);
        }
    },
    pay:function(){
        var info = {
            Product_Price:"1", 
            Product_Id:"monthly",  
            Product_Name:"gold",  
            Server_Id:"13",  
            Product_Count:"1",  
            Role_Id:"1001",  
            Role_Name:"asd"
        };
        iap_plugin.payForProduct(info);
        
    },
    onActionResult:function(plugin, code, msg){
        cc.log("on user result listener.")
        cc.log("code:"+code+",msg:"+msg)
        switch(code)
        {
        case anysdk.UserActionResultCode.kInitSuccess:
            //do
            break;
        case anysdk.UserActionResultCode.kInitFail:
            //do
            break;
        case anysdk.UserActionResultCode.kLoginSuccess:
            //do
            break;
        case anysdk.UserActionResultCode.kLoginNetworkError:
            //do
            break;
        case anysdk.UserActionResultCode.kLoginNoNeed:
            //do
            break;
        case anysdk.UserActionResultCode.kLoginFail:
            //do
            break;
        case anysdk.UserActionResultCode.kLoginCancel:
            //do
            break;
        case anysdk.UserActionResultCode.kLogoutSuccess:
            //do
            break;
        case anysdk.UserActionResultCode.kLogoutFail:
            //do
            break;
        case anysdk.UserActionResultCode.kPlatformEnter:
            //do
            break;
        case anysdk.UserActionResultCode.kPlatformBack:
            //do
            break;
        case anysdk.UserActionResultCode.kPausePage:
            //do
            break;
        case anysdk.UserActionResultCode.kExitPage:
            //do        
            break;
        case anysdk.UserActionResultCode.kAntiAddictionQuery:
            //do
            break;
        case anysdk.UserActionResultCode.kRealNameRegister:
            //do
            break;
        case anysdk.UserActionResultCode.kAccountSwitchSuccess:
            //do
            break;
        case anysdk.UserActionResultCode.kAccountSwitchFail:
            //do
            break;
        case anysdk.UserActionResultCode.kOpenShop:
            //do
            break;
        default:
            break;
        }
    },
    onPayResult:function(code, msg, info){
        cc.log("on iap result listener.")
        cc.log("code:"+code+",msg:"+msg)
        switch(code)
        {
        case anysdk.PayResultCode.kPaySuccess:
            //do
            break;
        case anysdk.PayResultCode.kPayFail:
            //do
            break;
        case anysdk.PayResultCode.kPayCancel:
            //do
            break;
        case anysdk.PayResultCode.kPayNetworkError:
            //do
            break;
        case anysdk.PayResultCode.kPayProductionInforIncomplete:
            //do
            break;
        case anysdk.PayResultCode.kPayInitSuccess:
            //do
            break;
        case anysdk.PayResultCode.kPayInitFail:
            //do
            break;
        case anysdk.PayResultCode.kPayNowPaying:
            //do
            break;
        default:
            break;
        }
    }

});