using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;		// UART; to support serial port function
using System.Runtime.InteropServices;
using System.Threading;
using System.IO;




namespace 温度采集上位机
{
    public partial class Form1 : Form
    {
        /*START OF URGUMENTS*/
        const short CMD_AMOUNT = 20;


        /*END OF URGUMENTS*/

        int[] TimeOverCountList = new int[CMD_AMOUNT];
        string[] Responsestring = new string[CMD_AMOUNT];
        string[] Commandstring = new string[CMD_AMOUNT];

        string FileName;


        public Form1()
        {
            InitializeComponent();




            FileName = DateTime.Today.ToString("yyyy-MM-dd") + ".csv";

            if (!File.Exists(FileName)  )
            {
                StreamWriter strmsave = new StreamWriter(FileName, false, System.Text.Encoding.UTF8);
                strmsave.Write("时间,点1温度,点2温度,点3温度,点4温度,点5温度,点6温度,点7温度,点8温度\r\n");
                strmsave.Close();
            }
            else
            {

            }




        }

        private void Form1_Load(object sender, EventArgs e)
        {
            UpdateSerialPortComboBox();
            System.Windows.Forms.Control.CheckForIllegalCrossThreadCalls = false;
            if (SerialPort_ComboBox.Items.Count != 0)
            {
                SerialPort_ComboBox.SelectedIndex = 0;
            }
            //
            TimeOverCountList[0] = 5;
            TimeOverCountList[1] = 3;
            TimeOverCountList[2] = 3;
            TimeOverCountList[3] = 3;
            TimeOverCountList[4] = 3;
            TimeOverCountList[5] = 3;
            TimeOverCountList[6] = 3;
            TimeOverCountList[7] = 3;
            TimeOverCountList[8] = 3;
            TimeOverCountList[9] = 3;
            TimeOverCountList[10] = 3;





            Commandstring[0] = "UPDATE THE DATA PLEASE";
            Commandstring[1] = "AT+UARTCFG=115200,1,0,0\r\n";//baud
            Commandstring[2] = "AT+DSCADDR=0,\"TCP\",\"mqtt.17cc.cn\",1883\r\n";//server1 ip&port
            Commandstring[3] = "AT+DSCADDR=0,\"TCP\",\"mqtt.17cc.cn\",1883\r\n";//server1 ip&port
            Commandstring[4] = "AT+KEEPALIVE=0,0,YD\r\n";//心跳包配置
            Commandstring[5] = "AT+ACKTIME=60\r\n";//掉线超时配置
            Commandstring[6] = "AT+DTUPACKET=100,0\r\n"; //配置打包时间和打包长度
            Commandstring[7] = "AT+RELINKTIME=5\r\n";//配置重连间隔时间
            Commandstring[8] = "AT+DSCTIME=120\r\n";//配置连接服务器超时时间
            Commandstring[9] = "AT&W\r\n";//保存刚才的配置
            Commandstring[10] = "AT+CFUN=1,1\r\n";////重启设备


            Responsestring[0] = "";//回复+++
            Responsestring[1] = "\r\nOK\r\n";
            Responsestring[2] = "\r\nOK\r\n";
            Responsestring[3] = "\r\nOK\r\n";
            Responsestring[4] = "\r\nOK\r\n";
            Responsestring[5] = "\r\nOK\r\n";
            Responsestring[6] = "\r\nOK\r\n";
            Responsestring[7] = "\r\nOK\r\n";
            Responsestring[8] = "\r\nOK\r\n";
            Responsestring[9] = "\r\nOK\r\n";
            Responsestring[10] = "\r\nOK\r\n";

            button_StartConfig.Enabled = false;

        }
        //


        private void UpdateSerialPortComboBox()
        {
            #region
            SerialPort_ComboBox.Items.Clear();
            SerialPort_ComboBox.SelectedIndex = -1;
            SerialPort_ComboBox.Text = "";
            #endregion

            string[] SerialPortName = SerialPort.GetPortNames();

            #region
            if (SerialPortName == null)
            {
                ControlSerialPortButton.Enabled = false;
                MessageBox.Show("没有检测到有效的串口！", "Error");
                return;
            }
            //
            #endregion


            #region
            foreach (string com in System.IO.Ports.SerialPort.GetPortNames())
            {
                bool Add2ItemEnable = true;
                SerialPort TestPortOpenOrnot = new SerialPort(com);

                TestPortOpenOrnot.PortName = com;
                TestPortOpenOrnot.BaudRate = 115200;
                TestPortOpenOrnot.DataBits = 8;
                TestPortOpenOrnot.StopBits = StopBits.One;
                TestPortOpenOrnot.Parity = Parity.None;

                try
                {
                    TestPortOpenOrnot.Open();
                }
                catch (UnauthorizedAccessException)
                {
                    Add2ItemEnable = false;
                }
                //

                TestPortOpenOrnot.Close();

                switch (Add2ItemEnable)
                {
                    case true:
                        SerialPort_ComboBox.Items.Add(com);
                        break;

                    case false:
                        break;
                }
                //

            }
            //
            #endregion


            #region
            if (SerialPort_ComboBox.Items.Count == 0)
            {
                MessageBox.Show("没有检测到有效的串口！", "Error");
                ControlSerialPortButton.Enabled = false;
            }
            //
            else
            {
                SerialPort_ComboBox.SelectedIndex = 0;
                ControlSerialPortButton.Enabled = true;
            }
            //
            #endregion

            
        }

        private void ControlSerialPortButton_Click(object sender, EventArgs e)
        {
            
            if (ControlSerialPortButton.Text == "打开串口")
            {
                SP.PortName = SerialPort_ComboBox.Text;
                SP.BaudRate = 115200;
                if (SP.BaudRate == 0)
                {
                    MessageBox.Show("Error：波特率参数不正确!", "Error");
                }
                //

                SP.DataBits = 8;
                if ((SP.DataBits != 8) && (SP.DataBits != 7) && (SP.DataBits != 6) && (SP.DataBits != 5))
                {
                    MessageBox.Show("Error：数据位参数不正确!", "Error");
                }
                //


                SP.StopBits = StopBits.One;
                SP.Parity = Parity.None;
                

                try
                {
                    //SysTick.Start();
                    SP.Open();
                    SerialPort_ComboBox.Enabled = false;

                }
                catch (System.UnauthorizedAccessException)
                {
                    MessageBox.Show("此串口已被其他程序占用，请重新选择！", "提示");
                    return;
                }

                button_StartConfig.Enabled = true;
            }
            //
            else
            {
                button_StartConfig.Enabled = false;
                SP.Close();
                SerialPort_ComboBox.Enabled = true;
            }
            //

            
            ControlSerialPortButton.Text = ControlSerialPortButton.Text == "打开串口" ? "已打开" : "打开串口";



        }

        private void button_StartConfig_Click(object sender, EventArgs e)
        {



            
            if (SP.IsOpen)
            {

                timer.Enabled = timer.Enabled == false ? true : false;

                if (label_Note.Text == "未采集数据")
                {
                    label_Note.Text = "正在采集数据";
                }
                else
                {
                    label_Note.Text = "未采集数据";
                }
                //

            }
            //
            else
            {
                MessageBox.Show("串口错误，未打开或串口号错误！");
            }
            //
        }

        private void SP_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            byte[] revData = new byte[1024];
            int revDataLen = 0;



            string ConvertChar2String;

            Thread.Sleep(10);

            revDataLen  =   SP.Read(revData, 0, SP.BytesToRead);
            ConvertChar2String = Encoding.UTF8.GetString(revData,0, revDataLen);



            //MessageBox.Show(DateTime.Now.ToLocalTime().ToString());


            //StreamWriter strmsave = new StreamWriter(FileName, false, System.Text.Encoding.UTF8);

            StreamWriter strmsave = File.AppendText(FileName);
            strmsave.Write(DateTime.Now.ToString()+ ","+ ConvertChar2String+"\r\n");
            strmsave.Close();

            textBox_Rev.Text = DateTime.Now.ToString() + "," + ConvertChar2String + "\r\n";



        }




        //
        [DllImport("msvcrt.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr memcmp(byte[] b1, byte[] b2, IntPtr count);

        private void timer_Tick(object sender, EventArgs e)
        {

            SP.Write(Commandstring[0]);

            label_Note.ForeColor = label_Note.ForeColor == Color.Blue ? Color.Red: Color.Blue;

        }

    }
}
