
var HelloWorldLayer = cc.Layer.extend({
    sprite:null,
    ctor:function () {
        //////////////////////////////
        // 1. super init first
        this._super();

        /////////////////////////////
        // 2. add a menu item with "X" image, which is clicked to quit the program
        //    you may modify it.
        // ask the window size
        var size = cc.winSize;

        // add a "close" icon to exit the progress. it's an autorelease object
        var closeItem = new cc.MenuItemImage(
            res.CloseNormal_png,
            res.CloseSelected_png,
            function () {
                cc.log("Menu is clicked!");
            }, this);
        closeItem.attr({
            x: size.width - 20,
            y: 20,
            anchorX: 0.5,
            anchorY: 0.5
        });

        var menu = new cc.Menu(closeItem);
        menu.x = 0;
        menu.y = 0;
        this.addChild(menu, 1);

        /////////////////////////////
        // 3. add your codes below...
        // add a label shows "Hello World"
        // create and initialize a label
        var helloLabel = new cc.LabelTTF("Hello World", "Arial", 38);
        // position the label on the center of the screen
        helloLabel.x = size.width / 2;
        helloLabel.y = 0;
        // add the label as a child to this layer
        this.addChild(helloLabel, 5);

        // add "HelloWorld" splash screen"
        this.sprite = new cc.Sprite(res.HelloWorld_png);
        this.sprite.attr({
            x: size.width / 2,
            y: size.height / 2,
            scale: 0.5,
            rotation: 180
        });
        this.addChild(this.sprite, 0);

        this.sprite.runAction(
            cc.sequence(
                cc.rotateTo(2, 0),
                cc.scaleTo(2, 1, 1)
            )
        );
        helloLabel.runAction(
            cc.spawn(
                cc.moveBy(2.5, cc.p(0, size.height - 40)),
                cc.tintTo(2.5,255,125,0)
            )
        );

        var aLy = new AgentLayer();
        cc.log("aLy: "+aLy);
        this.addChild(aLy);
        return true;
    }
});

var plugin_channel = null;
var _ads = null;
var _share = null;
var _push = null;
var _social = null;
var _analytics = null;

var menu_lv = {
    base:100,
    user:200,
    iap:300,
    share:400,
    ads:500,
    social:600,
    push:700,
    analytics:800
};
var user_operation = {
    login:0,
    logout:1,
    enterPlatform:2,
    showToolbar:3,
    hideToolbar:4,
    accountSwitch:5,
    realNameRegister:6,
    antiAddictionQuery:7,
    submitLoginGameRole:8
};
var iap_operation = {
    payForProduct:0
};
var share_operation = {
    share:0
};
var ads_operation = {
    preloadAds:0,
    showAds:1,
    hideAds:2,
    queryPoints:3,
    spendPoints:4
};
var social_operation = {
    submitScore:0,
    showLeaderboard:1,
    unlockAchievement:2,
    showAchievements:3
};
var push_operation = {
    startPush:0,
    closePush:1,
    setAlias:2,
    delAlias:3,
    setTags:4,
    delTags:5
};
var analytics_operation = {
    startSession:0,
    stopSession:1,
    logError:2,
    logEvent:3,
    setAccount:4,
    onchargeRequest:5,
    onChargeSuccess:6,
    onChargeOnlySuccess:7,
    onChargeFail:8
};
var AgentLayer = cc.Layer.extend({
    base_menu:null,
    sec_menu:null,
    sec_lys:null,
    is_dis_sec:false,
    i_cur_dis:-1,
    ctor:function () {
        this._super();

        plugin_channel = new PluginChannel();
        plugin_channel.loadPlugins();

        _ads = new Ads();
        _share = new Share();
        _push = new Push();
        _social = new Social();
        _analytics = new Analytics();
        // _analytics.startSession();

        this.base_menu = ["User System", "IAP System", "Share System", "Ads System", "Social System", "Push System", "Analytics System"];

        this.sec_menu = [
                    ["login", "logout", "enterPlatform", "showToolBar", "hideToolBar", "accountSwitch", "realNameRegister", "antiAddictionQuery", "submitLoginGameRole"],
                    ["payForProduct"],
                    ["share"],
                    ["preloadAds", "showAds", "hideAds", "queryPoints", "spendPoints"],
                    ["submitScore", "showLeaderboard", "unloackAchievement", "showAchievements"],
                    ["startPush", "closePush", "setAlias", "delAlias", "setTags", "delTags"],
                    ["startSession", "stopSession", "logError", "logEvent", "setAccount", "onchargeRequest", "onChargeSuccess", "onChargeOnlySuccess", "onChargeFail"]
                    ];

        this.sec_lys = [];
        var b_x = 130.0;
        var b_y = 400.0;
        var b_h = 60.0;
        var menu = cc.Menu.create();
        var arrBtns = [];
        for (var i = this.base_menu.length - 1; i >= 0; i--) {
            var btn = this.create_btn(this.base_menu[i], i);
            btn.setPosition(b_x, b_y - i*b_h);
            arrBtns.push(btn);
        };
        var menu = cc.Menu.create();
        menu.initWithArray(arrBtns);
        menu.x = 0;
        menu.y = 0;
        this.addChild(menu, 1);
    },
    create_btn:function(str, tag){
        var lb = cc.LabelTTF.create(str, "Arial", 38);
        var menuItem = cc.MenuItemLabel.create(lb, this.onClick.bind(this));
        menuItem.setTag(tag);
        return menuItem;
    },
    onClick:function(item){
        var tag = item.getTag();
        cc.log("click item: "+tag);
        if (tag < menu_lv.base){
            this.setSecInvisible();
            this.displaySecLayer(tag);
            this.i_cur_dis = tag;
        }
        else if (tag < menu_lv.user){
            this.onUserAction(tag - menu_lv.base);
        }
        else if (tag < menu_lv.iap){
            this.onIAPAction(tag - menu_lv.user);
        }
        else if (tag < menu_lv.share){
            this.onShareAction(tag - menu_lv.iap);
        }
        else if (tag < menu_lv.ads){
            this.onAdsAction(tag - menu_lv.share);
        }
        else if (tag < menu_lv.social){
            this.onSocialAction(tag - menu_lv.ads);
        }
        else if (tag < menu_lv.push){
            this.onPushAction(tag - menu_lv.social);
        }
        else if (tag < menu_lv.analytics){
            this.onAnalyticsAction(tag - menu_lv.push);
        }
    },
    setSecInvisible:function(){
        for (var i = this.sec_lys.length - 1; i >= 0; i--) {
            if (this.sec_lys[i] != null)
                this.sec_lys[i].setVisible(false);
        };
    },
    displaySecLayer:function(idx){
        if( this.is_dis_sec && idx == this.i_cur_dis){
            this.is_dis_sec = false;
            return;
        }
        if(this.sec_lys[idx] != null)
            this.sec_lys[idx].setVisible(true);
        else{
            var b_x = 530.0;
            var b_y = 400.0;
            var b_h = 55.0;
            if (idx == 0){
                b_y = 440.0;
                b_h = 48.0;
            }
            var menu = cc.Menu.create();
            var arrBtns = [];
            for (var i = this.sec_menu[idx].length - 1; i >= 0; i--) {
                var btn = this.create_btn(this.sec_menu[idx][i], i + 100*(idx+1));
                btn.setPosition(b_x, b_y - i*b_h);
                arrBtns.push(btn);
            };
            var menu = cc.Menu.create();
            menu.initWithArray(arrBtns);
            menu.x = 0;
            menu.y = 0;
            this.addChild(menu, 1);

            this.sec_lys[idx] = menu;
        }

        this.is_dis_sec = true;
    },
    onUserAction:function(idx){
        switch(idx){
            case user_operation.login:
                    plugin_channel.login();
                break;
            case user_operation.logout:
                    plugin_channel.logout();
                break;
            case user_operation.enterPlatform:
                    plugin_channel.enterPlatform();
                break;
            case user_operation.showToolbar:
                    plugin_channel.showToolbar(ToolBarPlace.kToolBarTopLeft);
                break;
            case user_operation.hideToolbar:
                    plugin_channel.hideToolbar();
                break;
            case user_operation.accountSwitch:
                    plugin_channel.accountSwitch();
                break;
            case user_operation.realNameRegister:
                    plugin_channel.realNameRegister();
                break;
            case user_operation.antiAddictionQuery:
                    plugin_channel.antiAddictionQuery();
                break;
            case user_operation.submitLoginGameRole:
                    plugin_channel.submitLoginGameRole();
                break;
        }
    },
    onIAPAction:function(idx){
        switch(idx){
            case iap_operation.payForProduct:
                plugin_channel.pay();
                break;
        }
    },
    onShareAction:function(idx){
        switch(idx){
            case share_operation.share:
                _share.share();
                break;
        }
    },
    onAdsAction:function(idx){
        switch(idx){
                case ads_operation.preloadAds:
                _ads.preloadAds(AdsType.AD_TYPE_FULLSCREEN);
                break;
            case ads_operation.showAds:
                _ads.showAds(AdsType.AD_TYPE_FULLSCREEN);
                break;
            case ads_operation.hideAds:
                _ads.hideAds(AdsType.AD_TYPE_FULLSCREEN);
                break;
            case ads_operation.queryPoints:
                _ads.queryPoints();
                break;
            case ads_operation.spendPoints:
                _ads.spendPoints(100);
                break;
        }
    },
    onSocialAction:function(idx){
        switch(idx){
            case social_operation.submitScore:
                _social.submitScore();
                break;
            case social_operation.showLeaderboard:
                _social.showLeaderboard();
                break;
            case social_operation.unlockAchievement:
                _social.unlockAchievement();
                break;
            case social_operation.showAchievements:
                _social.showAchievements();
                break;
        }
    },
    onPushAction:function(idx){
        switch(idx){
            case push_operation.startPush:
                _push.startPush();
                break;
            case push_operation.closePush:
                _push.closePush();
                break;
            case push_operation.setAlias:
                _push.setAlias();
                break;
            case push_operation.delAlias:
                _push.delAlias();
                break;
            case push_operation.setTags:
                _push.setTags();
                break;
            case push_operation.delTags:
                _push.delTags();
                break;
        }
    },
    onAnalyticsAction:function(idx){
        switch(idx){
            case analytics_operation.startSession:
                _analytics.startSession();
                break;
            case analytics_operation.stopSession:
                _analytics.stopSession();
                break;
            case analytics_operation.logError:
                _analytics.logError(1, "fail");
                break;
            case analytics_operation.logEvent:
                _analytics.logEvent(2, {key1:"value1", key2:"value2"});
                break;
            case analytics_operation.setAccount:
                 _analytics.setAccount();
                break;
            case analytics_operation.onchargeRequest:
                _analytics.onChargeRequest();
                break;
            case analytics_operation.onChargeSuccess:
                _analytics.onChargeSuccess();
                break;
            case analytics_operation.onChargeOnlySuccess:
                _analytics.onChargeOnlySuccess();
                break;
            case analytics_operation.onChargeFail:
                _analytics.onChargeFail();
                break;
        }
    }
});

var HelloWorldScene = cc.Scene.extend({
    onEnter:function () {
        this._super();
        var layer = new HelloWorldLayer();
        this.addChild(layer);
    }
});

