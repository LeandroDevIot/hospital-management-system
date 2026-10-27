namespace HospitalApi.Models;

public class Senha
{
    public int Id {get; set; }
    public string Codigo {get; set; } = string.Empty;
    public string Tipo {get; set; } = "Nomral";
    public string Status {get; set; } = "esperando_a_recepcao";
    public DateTime DataCriacao { get; set; } = DateTime.Now;
    public string Cpf {get; set; } = string.Empty; 

}