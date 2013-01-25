using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace RobotRysiu
{
    public partial class OknoGlowne : Form
    {
        DataTable Dane;
      
        public OknoGlowne()
        {
            InitializeComponent();
            Dane = new DataTable();

            for (int i = 0; i < 80; i++) Dane.Columns.Add();
            //Dane.Columns.
            for (int i = 0; i < 79; i++) Dane.Rows.Add();

          
         
            Mapa.RowTemplate.Height = 5;

           

            BindingSource bindingSource = new BindingSource();
            bindingSource.DataSource = Dane;
            Mapa.DataSource = bindingSource;

            for (int i = 0; i < 80; i++) Mapa.Columns[i].Width = 5;

            BaudRateBox.Items.Add("250000");
            BaudRateBox.Items.Add("9600");
            BaudRateBox.SelectedIndex = 0;

            COMPortBox.Items.Add("COM7");
            COMPortBox.SelectedIndex = 0;

            USART.BaudRate = 250000;
            USART.PortName = "COM7";
        }
        private void button1_Click(object sender, EventArgs e)
        {
            //USART.
            Dane.Rows[0][0] = "1";

           // Mapa.Rows[0].Cells[0].Style.BackColor = Color.Red;
             Mapa[0,0].Style.BackColor = Color.Red;

           // Mapa.Rows[1].Cells[2].Style.BackColor;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            USART.BaudRate = Convert.ToInt32(BaudRateBox.SelectedItem);
            USART.PortName = COMPortBox.SelectedItem.ToString();
           
            try
            {
                USART.Open();
                UsartColor.BackColor = Color.Green;
            }
            catch (Exception ex)
            {
                UsartColor.BackColor = Color.Red;
            }
           
        }

        private void button3_Click(object sender, EventArgs e)
        {
            if (USART.IsOpen)
            {
                USART.WriteLine(DataIn.Text);
                DataIn.Text = "";
            }
        }
    }
}
