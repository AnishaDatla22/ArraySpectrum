namespace WindowsFormsApplication1
{
    partial class Form1
    {
        /// <summary>
        /// 必要なデザイナ変数です。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 使用中のリソースをすべてクリーンアップします。
        /// </summary>
        /// <param name="disposing">マネージ リソースが破棄される場合 true、破棄されない場合は false です。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows フォーム デザイナで生成されたコード

        /// <summary>
        /// デザイナ サポートに必要なメソッドです。このメソッドの内容を
        /// コード エディタで変更しないでください。
        /// </summary>
        private void InitializeComponent()
        {
            this.btnDCamUSB = new System.Windows.Forms.Button();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.btnDCamTmpCtrl = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // btnDCamUSB
            // 
            this.btnDCamUSB.Location = new System.Drawing.Point(35, 27);
            this.btnDCamUSB.Name = "btnDCamUSB";
            this.btnDCamUSB.Size = new System.Drawing.Size(185, 56);
            this.btnDCamUSB.TabIndex = 0;
            this.btnDCamUSB.Text = "Control image device and acquisition";
            this.btnDCamUSB.UseVisualStyleBackColor = true;
            this.btnDCamUSB.Click += new System.EventHandler(this.btnDCamUSB_Click);
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(35, 109);
            this.textBox1.MaxLength = 60;
            this.textBox1.Multiline = true;
            this.textBox1.Name = "textBox1";
            this.textBox1.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.textBox1.Size = new System.Drawing.Size(439, 255);
            this.textBox1.TabIndex = 1;
            // 
            // btnDCamTmpCtrl
            // 
            this.btnDCamTmpCtrl.Location = new System.Drawing.Point(289, 27);
            this.btnDCamTmpCtrl.Name = "btnDCamTmpCtrl";
            this.btnDCamTmpCtrl.Size = new System.Drawing.Size(185, 56);
            this.btnDCamTmpCtrl.TabIndex = 0;
            this.btnDCamTmpCtrl.Text = "Control temperature functions";
            this.btnDCamTmpCtrl.UseVisualStyleBackColor = true;
            this.btnDCamTmpCtrl.Click += new System.EventHandler(this.btnDCamTmpCtrl_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(541, 400);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.btnDCamTmpCtrl);
            this.Controls.Add(this.btnDCamUSB);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btnDCamUSB;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.Button btnDCamTmpCtrl;
    }
}

