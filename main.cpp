#include <GL/gl.h> 					//biblioteca que permite todas as chamadas da API openGL
#include <GL/glut.h> 				//bibliotecao que permite a manipulação de janelas
#include <Math.h>                   //conjunto de funções para operações matemáticas

GLfloat escala=1;                  // variável para escala
GLfloat rotacao=0;                 // variável para rotação
GLfloat movex = 0, movey = 0;      // variáveis de movimentação para x e y

void quadrado(){
    glBegin(GL_QUADS);             //lBegin e glEnd delimitam os vértices que definem uma primitiva ou um grupo de primitivas semelhantes (definida como parâmetro).
        glColor3f(0,1,0);          //adiciona cor ao quadrado
        glVertex2f(-2,-2);         //adiciona um ponto na coordenada x, y que será usado para completar nosso quadrado
        glVertex2f(-2,2);          //adiciona um ponto na coordenada x, y que será usado para completar nosso quadrado
        glColor3f(1,0,0);          //adiciona cor ao quadrado
        glVertex2f(2,2);           //adiciona um ponto na coordenada x, y que será usado para completar nosso quadrado
        glVertex2f(2,-2);          //adiciona um ponto na coordenada x, y que será usado para completar nosso quadrado
    glEnd();
}


void desenhaObjeto(void){                 //função de desenho
    glClear(GL_COLOR_BUFFER_BIT);         //buffer padrão; limpa a tela toda vez que a função é chamada
	glMatrixMode(GL_PROJECTION);          //projeção dos pontos definidos no plano cartesiano
    glLoadIdentity(); 				      //carrega a projeção
    gluOrtho2D(-50,50,-50,50);            //define o tamanho do plano cartesiano
	glMatrixMode(GL_MODELVIEW);           //projeção do tipo modelo
    glLoadIdentity();                     //carrega essa identidade de projeção de modelo

    glPushMatrix();                           //insere a matriz de transformação corrente na pilha
        glScalef(escala, escala, 0);          //chama a fução escala e passa como parâmetro o valor da escala ( as mesmas para x e y)
        glRotatef(rotacao, 0,0,1);            //chama a fução rotação e passa como parâmetro o ângulo
        glTranslatef(movex, movey,0);         //chama a fução de tranlação e passa como parâmetro o valor para transladar em x e y
        quadrado();                           // chama a função que desenha um quadrado
    glPopMatrix();                            //retira a matriz do topo da pilha e torna esta última a matriz de transformação corrente

	glFlush();                                //carrega os comandos OpenGL (envia para o hardware os comandos, permitindo assim que os drivers GL iniciem o render)
}

/*função que atriui valores as nossas variáveis de escala e rotação (dependendo da tecla pressionada) */
void teclas(unsigned char tecla, GLint x, GLint y){
    switch(tecla){
        case '+': escala++;         // adiciona 1 ao valor de escala
        break;
        case '-': escala--;         // remove 1 ao valor de escala
        break;
        case '1': rotacao-=10;      // rotaciona o objeto no sentido horário (diminui o ângulo em 10)
        break;
        case '2': rotacao+=10;      // rotaciona o objeto no sentido anti-horário (aumenta o ângulo em 10)
        break;
    }
    glutPostRedisplay();            //redesenha a cena que está na janela
}

/*função que atriui valores as nossas variáveis de movimentação x e y (dependendo da tecla pressionada) */
void setasDirecionais(GLint tecla, GLint x, GLint y){
    switch(tecla){
        case GLUT_KEY_LEFT: movex--;               // move nosso objeto para a esquerda
        break;
        case GLUT_KEY_RIGHT: movex++;              // move nosso objeto para a direita
        break;
        case GLUT_KEY_UP: movey++;                 // move nosso objeto para cima
        break;
        case GLUT_KEY_DOWN: movey--;               // move nosso objeto para baixo
        break;
    }
    glutPostRedisplay();
}

int main(void){
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);                        // somente um buffer | sistema de cores RGB
    glutInitWindowSize(800,600);                                        // define o tamanho da janela
     glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH)-960)/2,         // medidas usadas para posicionar a janela no meio
                           (glutGet(GLUT_SCREEN_HEIGHT)-540)/2);        // da tela - isso depende da resolução do monitor
	glutCreateWindow("Exemplo - Teclado");                              // permite a criação de uma janela
    glutDisplayFunc(desenhaObjeto);                                     // função de callback - chama a função Desenha
    glutKeyboardFunc(teclas);                                           // Chamada da função teclado (cada pressionamento gera uma chamada do teclado)
    glutSpecialFunc(setasDirecionais);                                  // Chamada da função teclado especial (para quando as teclas direcionais são pressionadas)
    glClearColor(1,1,1,0);                                              // informa a cor de fundo da tela
    glutMainLoop();                                                     // loop infinito - escuta as informações do sistema até encerrar a aplicação
    return 0;                                                           // retorna zero
}
