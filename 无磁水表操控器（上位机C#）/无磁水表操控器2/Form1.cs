using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;
using System.Threading;

namespace 无磁水表操控器2
{
    public partial class Form1 : Form
    {
        public Form1()
        {            
            InitializeComponent();

            radioButton4.Checked = true;
            radioButton7.Checked = true;
            radioButton10.Checked = true;
            radioButton13.Checked = true;
            comboBox1.Items.Clear();
            foreach (string item in SerialPort.GetPortNames())
            {
                comboBox1.Items.Add(item);
            }

            comboBox1.Text = "请选择串口";
        }
        byte[] sendBuff = new byte[11] { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };
        private void button1_Click(object sender, EventArgs e)
        {

            #region 帧头帧尾
            Array.Clear(sendBuff, 0, 11);
            sendBuff[0] = 0x68;
            sendBuff[1] = 0x86;
            sendBuff[10]= 0x80;          
            #endregion
            #region 阀门控制
            if (radioButton1.Checked)
            {
                sendBuff[2] = 0x10;
            }
            if (radioButton2.Checked)
            {
                sendBuff[2] = 0x20;
            }
            if (radioButton3.Checked)
            {
                sendBuff[2] = 0x30;
            }
            if (radioButton4.Checked)
            {
                sendBuff[2] = 0xff;
            }
            #endregion
            #region 液晶控制
            if (radioButton5.Checked)
            {
                sendBuff[3] = 0x10;
            }
            if (radioButton6.Checked)
            {
                sendBuff[3] = 0x20;
            }
            if (radioButton7.Checked)
            {
                sendBuff[3] = 0xff;
            }
            #endregion
            #region 用水管理
            if (radioButton8.Checked)
            {
                sendBuff[4] = 0x40;
            }
            if (radioButton9.Checked)
            {
                sendBuff[4] = 0x60;
                decimal WaterVolume = numericUpDown1.Value;
                UInt32 WaterVolumeSend = Convert.ToUInt32(WaterVolume);
                sendBuff[6] = (byte)(WaterVolumeSend >> 24);
                sendBuff[7] = (byte)(WaterVolumeSend >> 16);
                sendBuff[8] = (byte)(WaterVolumeSend >> 8);
                sendBuff[9] = (byte)(WaterVolumeSend);
            }
            if (radioButton10.Checked)
            {
                sendBuff[4] = 0xff;
            }
            #endregion
            #region 数据存储
            if (radioButton11.Checked)
            {
                sendBuff[5] = 0x90;
            }
            if (radioButton12.Checked)
            {
                sendBuff[5] = 0xa0;
            }
            if (radioButton13.Checked)
            {
                sendBuff[5] = 0xff;
            }
            #endregion
            if (serialPort1.IsOpen)
            {

                label3.Text = "发送的命令：\n";
                label4.Text = "接收的命令：";              
                #region 发送命令显示处理
                UInt16 iSendBuffCnt = 0;
                foreach (byte item in sendBuff)
                {
                    iSendBuffCnt++;
                    label3.Text += item.ToString() + ' ';
                    if((iSendBuffCnt == 2)||(iSendBuffCnt == 10))
                    {
                        label3.Text += '\n';
                    }
                    radioButton4.Checked = true;
                    radioButton7.Checked = true;
                    radioButton10.Checked = true;
                    radioButton13.Checked = true;
                }
                #endregion                
                serialPort1.Write(sendBuff,0,11);                
            }
            else
            {
                button1.Text = "请打开串口";
            }
            
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (serialPort1.IsOpen)
            {
                serialPort1.Close();
                button3.Text = "打开串口";
                button1.Text = "发送";
            }
        }

        private void button2_Click(object sender, EventArgs e)                              //按键2：重新搜索串口
        {
            comboBox1.Items.Clear();
            if (serialPort1.IsOpen)
            {
                serialPort1.Close();
                button3.Text = "打开串口";
            }
            foreach (string item in SerialPort.GetPortNames())
            {
                comboBox1.Items.Add(item);
            }
            comboBox1.Text = comboBox1.Items[0].ToString();
        }

        private void button3_Click(object sender, EventArgs e)                              //按键3：打开/关闭串口
        {
            if (serialPort1.IsOpen)
            {
                button3.Text = "打开串口";
                serialPort1.Close();
            }
            else
            {
                button3.Text = "关闭串口";
                button1.Text = "发送";
                serialPort1.PortName = comboBox1.Text;
                serialPort1.Open();
            }
        }

        private void serialPort1_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            Thread.Sleep(50);
            byte[] RXbuff = new byte[7];
            serialPort1.Read(RXbuff, 0, 7);
            if ((RXbuff[0] == 0x86) && (RXbuff[1] == 0x68)&&(RXbuff[6] == 0x08))
            {
                Swap(ref RXbuff[2], ref RXbuff[5]);
                Swap(ref RXbuff[3], ref RXbuff[4]);
                UInt32 WaterVolumeDisplay = BitConverter.ToUInt32(RXbuff, 2);
                this.Invoke(new EventHandler(delegate
                {
                    label4.Text = "接收的命令:\n";
                    UInt16 iRXbuffCnt = 0;
                    foreach (byte item in RXbuff)
                    {                        
                        if ((iRXbuffCnt == 2) || (iRXbuffCnt == 6))
                        {
                            label4.Text += '\n';
                        }
                        iRXbuffCnt++;
                        label4.Text += item.ToString() + ' '; 
                    }
                     
                    label2.Text = "当前用水量：" + Convert.ToDecimal(WaterVolumeDisplay);
                }));


            }
        }
        static void Swap<T>(ref T a, ref T b)
        {
            T t = a;
            a = b;
            b = t;
        }

    }
}
