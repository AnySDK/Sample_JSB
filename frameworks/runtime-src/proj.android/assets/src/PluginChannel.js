

//注意：这里appKey, appSecret, privateKey，要替换成自己打包工具里面的值(登录打包工具，游戏管理界面上显示的那三个参数)
var appKey = "0914CB16-BAEE-790E-808E-3A37B8FFBE3F";
var appSecret = "62bee0ddb86bdeccb8acd959765041cc";
var privateKey = "96C273AB03E1A798BA1AD0C38004871F";
var oauthLoginServer = "http://oauth.anysdk.com/api/OauthLoginDemo/Login.php";

var agent = null;
var user_plugin = null;
var iap_pluginMap = null;
var analytics_plugin = null;

var PluginChannel = cc.Class.extend({
	loadPlugins:function(){
        agent = anysdk.AgentManager.getInstance();
        // init
        agent.init(appKey,appSecret,privateKey,oauthLoginServer);
        //cc.log("getChannelId"+ agent.getChannelId());
        //cc.log("getFrameworkVersion"+ agent.getFrameworkVersion());
        // load
        agent.loadAllPlugins();
        // get plugins
        user_plugin   = agent.getUserPlugin();
        iap_pluginMap = agent.getIAPPlugin();
                                    analytics_plugin = agent.getAnalyticsPlugin();

        //cc.log("");
        if (user_plugin) {
        	user_plugin.setActionListener(this.onActionResult, this);
        }

        for(var key in iap_pluginMap){
            var iap_plugin = iap_pluginMap[key];
            iap_plugin.setResultListener(this.onPayResult, this);
        }
                                    if(analytics_plugin){
                                    analytics_plugin.startSession();
                                    var data = anysdk.PluginParam.create({roleId:"123456",roleName:"test",roleLevel:"10",zoneId:"123",zoneName:"test",dataType:"1",ext:"login"});
                                    analytics_plugin.callFuncWithParam("setAccount", data);
                                    }
        this.funcOfAgent();
	},
    funcOfAgent:function(){
        var customParam = agent.getCustomParam();
        cc.log("customParam:"+customParam);
//        var channelId = agent.getChannelId();
//        cc.log("channelId:"+channelId);
    },
    login:function(){
    	user_plugin.login();
    },
    logout:function(){
    	if ( user_plugin.isFunctionSupported("logout") )
    		user_plugin.callFuncWithParam("logout");
    },
    enterPlatform:function(){
    	if ( user_plugin.isFunctionSupported("enterPlatform") )
    		user_plugin.callFuncWithParam("enterPlatform");
    },
    showToolbar:function(pos){
        if ( user_plugin.isFunctionSupported("showToolBar") ){
            var param1 = anysdk.PluginParam.create(pos);
            user_plugin.callFuncWithParam("showToolBar", param1);
        }
    },
    hideToolbar:function(){
        if ( user_plugin.isFunctionSupported("hideToolBar") )
            user_plugin.callFuncWithParam("hideToolBar");
    },
    accountSwitch:function(){
        if ( user_plugin.isFunctionSupported("accountSwitch") )
            user_plugin.callFuncWithParam("accountSwitch");
    },
    realNameRegister:function(){
        if ( user_plugin.isFunctionSupported("realNameRegister") )
            user_plugin.callFuncWithParam("realNameRegister");
    },
    antiAddictionQuery:function(){
        if ( user_plugin.isFunctionSupported("antiAddictionQuery") )
            user_plugin.callFuncWithParam("antiAddictionQuery");
    },
    submitLoginGameRole:function(){
        if( user_plugin.isFunctionSupported("submitLoginGameRole") ){
            var data = anysdk.PluginParam.create({roleId:"123456",roleName:"test",roleLevel:"10",zoneId:"123",zoneName:"test",dataType:"1",ext:"login"});
            user_plugin.callFuncWithParam("submitLoginGameRole", data);
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
        for(var p in iap_pluginMap){
            var iap_plugin = iap_pluginMap[p];
            cc.log("will pay for product");
            //iap_plugin.payForProduct(info);
            var param1 = anysdk.PluginParam.create("PD_10005");
            iap_plugin.callFuncWithParam("requestProducts", param1);
        }
    },
    onActionResult:function(plugin, code, msg){
        cc.log("on user result listener.")
        cc.log("code:"+code+",msg:"+msg)
        switch(code)
        {
        case UserActionResultCode.kInitSuccess:
            //do
            break;
        case UserActionResultCode.kInitFail:
            //do
            break;
        case UserActionResultCode.kLoginSuccess:
            //do
            break;
        case UserActionResultCode.kLoginNetworkError:
            //do
            break;
        case UserActionResultCode.kLoginNoNeed:
            //do
            break;
        case UserActionResultCode.kLoginFail:
            //do
            break;
        case UserActionResultCode.kLoginCancel:
            //do
            break;
        case UserActionResultCode.kLogoutSuccess:
            //do
            break;
        case UserActionResultCode.kLogoutFail:
            //do
            break;
        case UserActionResultCode.kPlatformEnter:
            //do
            break;
        case UserActionResultCode.kPlatformBack:
            //do
            break;
        case UserActionResultCode.kPausePage:
            //do
            break;
        case UserActionResultCode.kExitPage:
            //do        
            break;
        case UserActionResultCode.kAntiAddictionQuery:
            //do
            break;
        case UserActionResultCode.kRealNameRegister:
            //do
            break;
        case UserActionResultCode.kAccountSwitchSuccess:
            //do
            break;
        case UserActionResultCode.kAccountSwitchFail:
            //do
            break;
        case UserActionResultCode.kOpenShop:
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
        case PayResultCode.kPaySuccess:
            //do
            break;
        case PayResultCode.kPayFail:
            //do
            break;
        case PayResultCode.kPayCancel:
            //do
            break;
        case PayResultCode.kPayNetworkError:
            //do
            break;
        case PayResultCode.kPayProductionInforIncomplete:
            //do
            break;
        case PayResultCode.kPayInitSuccess:
            //do
            break;
        case PayResultCode.kPayInitFail:
            //do
            break;
        case PayResultCode.kPayNowPaying:
            //do
            break;
        default:
            break;
        }
    }

});