using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;

namespace WindowsFormsApp1
{
    public partial class Form1 : Form
    {
        private int itemNumber = 1;
        public Form1()
        {
            InitializeComponent();
            // Добавляем операции в comboBox1
            comboBox1.Items.Add("+");
            comboBox1.Items.Add("-");
            comboBox1.Items.Add("*");
            comboBox1.SelectedIndex = 0; // Выбираем первый элемент по умолчанию
        }

    

        private void button1_Click_1(object sender, EventArgs e)
        {
            // Проверяем, что текстовое поле не пустое
            if (!string.IsNullOrWhiteSpace(textBox1.Text))
            {
                // Добавляем текст из textBox1 в listBox1 с номером
                listBox1.Items.Add($"{itemNumber}. {textBox1.Text}");

                // Увеличиваем счетчик для следующего элемента
                itemNumber++;

                // Очищаем текстовое поле после добавления
                textBox1.Clear();
            }
            else
            {
                // Если текстовое поле пустое, выводим сообщение
                MessageBox.Show("Введите текст в текстовое поле!", "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }

        }

        private void button2_Click(object sender, EventArgs e)
        {
            // Проверяем, что textBox2 и textBox3 не пустые
            if (!string.IsNullOrWhiteSpace(textBox2.Text) && !string.IsNullOrWhiteSpace(textBox3.Text))
            {
                // Создаем объекты Polinom на основе введенных данных
                Polinom polinom1, polinom2;
                try
                {
                    polinom1 = Polinom.Parse(textBox2.Text);
                    polinom2 = Polinom.Parse(textBox3.Text);
                }
                catch (Exception ex)
                {
                    MessageBox.Show("Ошибка при парсинге полиномов: " + ex.Message, "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    return;
                }

                // Получаем выбранную операцию из comboBox1
                string operation = comboBox1.SelectedItem.ToString();

                // Выполняем операцию
                Polinom result;
                if (operation == "+")
                {
                    result = polinom1 + polinom2;
                }
                else if (operation == "-")
                {
                    result = polinom1 - polinom2;
                }
                else if (operation == "*")
                {
                    result = polinom1 * polinom2;
                }
                else
                {
                    MessageBox.Show("Неизвестная операция!", "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    return;
                }

                // Добавляем результат в listBox1 с номером
                listBox1.Items.Add($"{itemNumber}. {polinom1} {operation} {polinom2} = {result}");

                // Увеличиваем счетчик для следующего элемента
                itemNumber++;
            }
            else
            {
                MessageBox.Show("Заполните оба поля!", "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
        }
    }

    // Пример класса Polinom (заглушка)
    public class Polinom
    {
        public static Polinom Parse(string input)
        {
            // Здесь должна быть реализация парсинга строки в Polinom
            return new Polinom();
        }

        public static Polinom operator +(Polinom a, Polinom b)
        {
            // Здесь должна быть реализация сложения
            return new Polinom();
        }

        public static Polinom operator -(Polinom a, Polinom b)
        {
            // Здесь должна быть реализация вычитания
            return new Polinom();
        }

        public static Polinom operator *(Polinom a, Polinom b)
        {
            // Здесь должна быть реализация умножения
            return new Polinom();
        }

        public override string ToString()
        {
            // Здесь должна быть реализация преобразования Polinom в строку
            return "Polinom";
        }
    }
}
