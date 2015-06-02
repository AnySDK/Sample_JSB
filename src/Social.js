
var social_plugin = null;

var Social = cc.Class.extend({
	ctor:function(){
		social_plugin = anysdk.AgentManager.getInstance().getSocialPlugin();
        // set share result listener
        if (social_plugin)
            social_plugin.setListener(this.onActionResult, this);
	},
	submitScore:function(){
        var score = 131;
        social_plugin.submitScore("friend", score);
	},
	showLeaderboard:function(){
		social_plugin.showLeaderboard("friend");
	},
	unlockAchievement:function(){
        var achInfo = {"rank":"friends"}
        social_plugin.unlockAchievement(achInfo);
	},
	showAchievements:function(){
		social_plugin.showAchievements();
	},
	signIn:function(){
		social_plugin.signIn();
	},
	signOut:function(){
		social_plugin.signOut();
	},
	onActionResult:function(code, msg){
		cc.log("on social result listener.")
		cc.log("code:"+code+",msg:"+msg)
		switch(code)
		{
			case SocialRetCode.kScoreSubmitSucceed:
				//do
				break;
			case SocialRetCode.kScoreSubmitfail:
				//do
				break;
			case SocialRetCode.kAchUnlockSucceed:
				//do
				break;
			case SocialRetCode.kAchUnlockFail:
				//do
				break;
			case SocialRetCode.kSocialSignInSucceed:
				//do
				break;
			case SocialRetCode.kSocialSignOutSucceed:
				//do
				break;
			case SocialRetCode.kSocialSignOutFail:
				//do
				break;
			case SocialRetCode.kSocialSignOutFail:
				//do
				break;
			case SocialRetCode.kSocialGetGameFriends:
				//do
				break;
		}
	}
});