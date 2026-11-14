package org.cocos2dx.cpp;
import android.os.Bundle;
import org.cocos2dx.lib.Cocos2dxActivity;
public class AppActivity extends Cocos2dxActivity {
 @Override protected void onCreate(Bundle state){super.setEnableVirtualButton(false);super.onCreate(state);}
}