package org.appinventor;
import com.google.appinventor.components.runtime.HandlesEventDispatching;
import com.google.appinventor.components.runtime.EventDispatcher;
import com.google.appinventor.components.runtime.Form;
import com.google.appinventor.components.runtime.Component;
import com.google.appinventor.components.runtime.Label;
import com.google.appinventor.components.runtime.ListPicker;
import com.google.appinventor.components.runtime.Button;
import com.google.appinventor.components.runtime.Image;
import com.google.appinventor.components.runtime.BluetoothClient;
import com.google.appinventor.components.runtime.util.YailList;
class Screen1 extends Form implements HandlesEventDispatching {
  private Label Label1;
  private ListPicker ListPicker1;
  private Button Button1;
  private Button Button2;
  private Image Image1;
  private BluetoothClient BluetoothClient1;
  protected void $define() {
    this.AppName("CSE_412_Final");
    this.Title("Screen1");
    Label1 = new Label(this);
    Label1.BackgroundColor(0xFF000000);
    Label1.FontBold(true);
    Label1.FontSize(20);
    Label1.Height(LENGTH_FILL_PARENT);
    Label1.Width(LENGTH_FILL_PARENT);
    Label1.Text("CSE 412 Final Project - Group 14");
    Label1.TextColor(0xFFFFFFFF);
    ListPicker1 = new ListPicker(this);
    ListPicker1.Height(LENGTH_FILL_PARENT);
    ListPicker1.Width(LENGTH_FILL_PARENT);
    ListPicker1.Text("CONNECT TO BLUETOOTH");
    ListPicker1.Title("Bluetooth");
    Button1 = new Button(this);
    Button1.Height(LENGTH_FILL_PARENT);
    Button1.Width(LENGTH_FILL_PARENT);
    Button1.Text("ON");
    Button2 = new Button(this);
    Button2.Height(LENGTH_FILL_PARENT);
    Button2.Width(LENGTH_FILL_PARENT);
    Button2.Text("OFF");
    Image1 = new Image(this);
    Image1.Height(-1050);
    Image1.Width(LENGTH_FILL_PARENT);
    Image1.Picture("3772104.jpg");
    Image1.ScalePictureToFit(true);
    BluetoothClient1 = new BluetoothClient(this);
    EventDispatcher.registerEventForDelegation(this, "BeforePickingEvent", "BeforePicking" );
    EventDispatcher.registerEventForDelegation(this, "AfterPickingEvent", "AfterPicking" );
    EventDispatcher.registerEventForDelegation(this, "ClickEvent", "Click" );
  }
  public boolean dispatchEvent(Component component, String componentName, String eventName, Object[] params){
    if( component.equals(ListPicker1) && eventName.equals("BeforePicking") ){
      ListPicker1BeforePicking();
      return true;
    }
    if( component.equals(ListPicker1) && eventName.equals("AfterPicking") ){
      ListPicker1AfterPicking();
      return true;
    }
    if( component.equals(Button1) && eventName.equals("Click") ){
      Button1Click();
      return true;
    }
    if( component.equals(Button2) && eventName.equals("Click") ){
      Button2Click();
      return true;
    }
    return false;
  }
  public void ListPicker1BeforePicking(){
    ListPicker1.Elements(YailList.makeList(BluetoothClient1.AddressesAndNames()));
  }
  public void ListPicker1AfterPicking(){
    ListPicker1.Selection(BluetoothClient1.Connect(ListPicker1.Selection()));
    ListPicker1.Text("Connection Successful!");
  }
  public void Button1Click(){
    BluetoothClient1.Send1ByteNumber(String.valueOf(1));
  }
  public void Button2Click(){
    BluetoothClient1.Send1ByteNumber(String.valueOf(0));
  }
}