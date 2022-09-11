public class Exame {
    public Exame(Medico medico, Paciente paciente, String descricao, String resultado){
        this.medico = medico;
        this.paciente = paciente;
        this.descricao = descricao;
        this.resultado = resultado;
    }

    Medico medico;
    Paciente paciente;
    String descricao;
    String resultado;

    public void imprimirExame(){
        System.out.print("Exame realizado por - \n");
        System.out.printf("Medico: %s\n", medico.nome);
        System.out.printf("CRM: %s\n", medico.crm);
        System.out.printf("Especializado em: %s\n\n", medico.especializacao);

        System.out.print("Paciente: ");
        System.out.printf("Nome: %s\n", paciente.nome);
        System.out.printf("CPF: %s\n", paciente.cpf);
        System.out.printf("Idade: %s\n\n", paciente.idade);

        System.out.printf("Exame de: %s\n", descricao);
        System.out.printf("Resultado: %s\n", resultado);
    }
}
