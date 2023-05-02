# OpenMP tasks

### **O que são OpenMP tasks**
  
  OpenMP task é uma linha unica de código ou uma estrutura de bloco que é imediatamente "escrita em baixo" numa lista de tarefas(tasks).
  
  A nova tarefa pode ser executada imediatamente, ou pode ser adiada. Se o "if" é usado e o argumento resulta em 0, então a tarefa é executada imediatamente, suspendendo qualquer coisa que a thread estava fazendo. Claro, para isso funcionar tem que ter uma equipe de escadeamento paralelo. Se não houver, uma thread acaba fazendo todas as tarefas e não haverá contribuição para o paralelismo.

---

### **Como utilizar**

Pode ser criado uma *task barrier* que fará todas as tasks esperar até todas estiverem completas: 

    #pragma omp taskwait

*Omp task* define uma terefa mas não sua ordem de execução nem o momento da execução

    #pragma omp task


*firstprivate* copia o valor atual de uma variavel 'x' na task e imadiatemente a torna privada

    #pragma omp task firstprivate(x)
---

- Exemplos de utilização
  
---

- Qual a diferença para as OpenMP Sections

OpenMP tasks são bem parecidos com o OpenMP Sections, mas o Sections são 'static', que é, o número de seções que é setado quando é escrito um código, por outro lado, as 'tasks' são mais dinâmicas simples e rápida, e podem ser criadas a qualquer momento, e em qualquer quantidade dependendo da lógica que você aplica no programa.

---

- Quando utilizar ? (em que tipo de problemas)


