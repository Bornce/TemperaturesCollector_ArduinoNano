namespace 温度采集上位机
{
    partial class Form1
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.SP = new System.IO.Ports.SerialPort(this.components);
            this.SerialPort_ComboBox = new System.Windows.Forms.ComboBox();
            this.label_串口号 = new System.Windows.Forms.Label();
            this.ControlSerialPortButton = new System.Windows.Forms.Button();
            this.button_StartConfig = new System.Windows.Forms.Button();
            this.timer = new System.Windows.Forms.Timer(this.components);
            this.label_Note = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.textBox_Rev = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // SP
            // 
            this.SP.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.SP_DataReceived);
            // 
            // SerialPort_ComboBox
            // 
            this.SerialPort_ComboBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 11F);
            this.SerialPort_ComboBox.FormattingEnabled = true;
            this.SerialPort_ComboBox.Location = new System.Drawing.Point(91, 31);
            this.SerialPort_ComboBox.Name = "SerialPort_ComboBox";
            this.SerialPort_ComboBox.Size = new System.Drawing.Size(136, 26);
            this.SerialPort_ComboBox.TabIndex = 4;
            // 
            // label_串口号
            // 
            this.label_串口号.AutoSize = true;
            this.label_串口号.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label_串口号.Location = new System.Drawing.Point(12, 35);
            this.label_串口号.Name = "label_串口号";
            this.label_串口号.Size = new System.Drawing.Size(56, 16);
            this.label_串口号.TabIndex = 5;
            this.label_串口号.Text = "串口号";
            // 
            // ControlSerialPortButton
            // 
            this.ControlSerialPortButton.Font = new System.Drawing.Font("宋体", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.ControlSerialPortButton.ImageAlign = System.Drawing.ContentAlignment.TopLeft;
            this.ControlSerialPortButton.Location = new System.Drawing.Point(112, 91);
            this.ControlSerialPortButton.Name = "ControlSerialPortButton";
            this.ControlSerialPortButton.Size = new System.Drawing.Size(74, 25);
            this.ControlSerialPortButton.TabIndex = 6;
            this.ControlSerialPortButton.Text = "打开串口";
            this.ControlSerialPortButton.UseVisualStyleBackColor = true;
            this.ControlSerialPortButton.Click += new System.EventHandler(this.ControlSerialPortButton_Click);
            // 
            // button_StartConfig
            // 
            this.button_StartConfig.Font = new System.Drawing.Font("华文中宋", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.button_StartConfig.Location = new System.Drawing.Point(78, 253);
            this.button_StartConfig.Name = "button_StartConfig";
            this.button_StartConfig.Size = new System.Drawing.Size(139, 49);
            this.button_StartConfig.TabIndex = 7;
            this.button_StartConfig.Text = "StartConfig";
            this.button_StartConfig.UseVisualStyleBackColor = true;
            this.button_StartConfig.Click += new System.EventHandler(this.button_StartConfig_Click);
            // 
            // timer
            // 
            this.timer.Interval = 30000;
            this.timer.Tick += new System.EventHandler(this.timer_Tick);
            // 
            // label_Note
            // 
            this.label_Note.AutoSize = true;
            this.label_Note.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label_Note.Location = new System.Drawing.Point(106, 119);
            this.label_Note.Name = "label_Note";
            this.label_Note.Size = new System.Drawing.Size(88, 16);
            this.label_Note.TabIndex = 8;
            this.label_Note.Text = "未采集数据";
            this.label_Note.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.ForeColor = System.Drawing.Color.Gray;
            this.label1.Location = new System.Drawing.Point(183, 306);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(113, 12);
            this.label1.TabIndex = 9;
            this.label1.Text = "版权所有：Alex-BNS";
            // 
            // textBox_Rev
            // 
            this.textBox_Rev.Location = new System.Drawing.Point(15, 176);
            this.textBox_Rev.Multiline = true;
            this.textBox_Rev.Name = "textBox_Rev";
            this.textBox_Rev.Size = new System.Drawing.Size(284, 45);
            this.textBox_Rev.TabIndex = 10;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(308, 327);
            this.Controls.Add(this.textBox_Rev);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.label_Note);
            this.Controls.Add(this.button_StartConfig);
            this.Controls.Add(this.ControlSerialPortButton);
            this.Controls.Add(this.label_串口号);
            this.Controls.Add(this.SerialPort_ComboBox);
            this.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(192)))), ((int)(((byte)(0)))), ((int)(((byte)(0)))));
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "Form1";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "温度采集系统";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.IO.Ports.SerialPort SP;
        private System.Windows.Forms.ComboBox SerialPort_ComboBox;
        private System.Windows.Forms.Label label_串口号;
        private System.Windows.Forms.Button ControlSerialPortButton;
        private System.Windows.Forms.Button button_StartConfig;
        private System.Windows.Forms.Timer timer;
        private System.Windows.Forms.Label label_Note;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox textBox_Rev;
    }
}

