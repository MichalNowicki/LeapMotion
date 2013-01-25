namespace RobotRysiu
{
    partial class OknoGlowne
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.Mapa = new System.Windows.Forms.DataGridView();
            this.button1 = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.USART = new System.IO.Ports.SerialPort(this.components);
            this.BaudRateBox = new System.Windows.Forms.ComboBox();
            this.COMPortBox = new System.Windows.Forms.ComboBox();
            this.button2 = new System.Windows.Forms.Button();
            this.UsartColor = new System.Windows.Forms.Panel();
            this.DataIn = new System.Windows.Forms.TextBox();
            this.button3 = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.Mapa)).BeginInit();
            this.SuspendLayout();
            // 
            // Mapa
            // 
            this.Mapa.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.Mapa.ColumnHeadersVisible = false;
            this.Mapa.Location = new System.Drawing.Point(45, 60);
            this.Mapa.Name = "Mapa";
            this.Mapa.RowHeadersVisible = false;
            this.Mapa.Size = new System.Drawing.Size(403, 403);
            this.Mapa.TabIndex = 0;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(512, 391);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(159, 72);
            this.button1.TabIndex = 1;
            this.button1.Text = "button1";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 24F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.label1.Location = new System.Drawing.Point(202, 20);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(97, 37);
            this.label1.TabIndex = 2;
            this.label1.Text = "Mapa";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.label2.Location = new System.Drawing.Point(507, 29);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(164, 25);
            this.label2.TabIndex = 3;
            this.label2.Text = "USART settings";
            // 
            // USART
            // 
            this.USART.BaudRate = 250000;
            this.USART.PortName = "COM7";
            // 
            // BaudRateBox
            // 
            this.BaudRateBox.FormattingEnabled = true;
            this.BaudRateBox.Location = new System.Drawing.Point(519, 83);
            this.BaudRateBox.Name = "BaudRateBox";
            this.BaudRateBox.Size = new System.Drawing.Size(140, 21);
            this.BaudRateBox.TabIndex = 4;
            // 
            // COMPortBox
            // 
            this.COMPortBox.FormattingEnabled = true;
            this.COMPortBox.Location = new System.Drawing.Point(519, 110);
            this.COMPortBox.Name = "COMPortBox";
            this.COMPortBox.Size = new System.Drawing.Size(140, 21);
            this.COMPortBox.TabIndex = 5;
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(519, 147);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(96, 33);
            this.button2.TabIndex = 6;
            this.button2.Text = "Open";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // UsartColor
            // 
            this.UsartColor.BackColor = System.Drawing.Color.Red;
            this.UsartColor.Location = new System.Drawing.Point(625, 147);
            this.UsartColor.Name = "UsartColor";
            this.UsartColor.Size = new System.Drawing.Size(34, 32);
            this.UsartColor.TabIndex = 7;
            // 
            // DataIn
            // 
            this.DataIn.Location = new System.Drawing.Point(524, 217);
            this.DataIn.Name = "DataIn";
            this.DataIn.Size = new System.Drawing.Size(134, 20);
            this.DataIn.TabIndex = 8;
            // 
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(522, 247);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(136, 46);
            this.button3.TabIndex = 9;
            this.button3.Text = "Send";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.button3_Click);
            // 
            // OknoGlowne
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(700, 484);
            this.Controls.Add(this.button3);
            this.Controls.Add(this.DataIn);
            this.Controls.Add(this.UsartColor);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.COMPortBox);
            this.Controls.Add(this.BaudRateBox);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.Mapa);
            this.Name = "OknoGlowne";
            this.Text = "RobotRysiu:)";
            ((System.ComponentModel.ISupportInitialize)(this.Mapa)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataGridView Mapa;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.IO.Ports.SerialPort USART;
        private System.Windows.Forms.ComboBox BaudRateBox;
        private System.Windows.Forms.ComboBox COMPortBox;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Panel UsartColor;
        private System.Windows.Forms.TextBox DataIn;
        private System.Windows.Forms.Button button3;
    }
}

