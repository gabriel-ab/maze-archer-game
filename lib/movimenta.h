#define VELOCIDADE_MAX 2
#define ACELERACAO 0.15
#define TAXA_ATRITO 0.1

int colisaoCima(Personagem *fulano, Rectangle *MAPA);
int colisaoBaixo(Personagem *fulano, Rectangle *MAPA);
int colisaoEsquerda(Personagem *fulano, Rectangle *MAPA);
int colisaoDireita(Personagem *fulano, Rectangle *MAPA);

void atualizarColisao(Personagem *fulano);
void aplicarInercia(Personagem *fulano);
void aplicarAtrito(Personagem *fulano, float taxa);

void movimentar(Personagem *fulano, Rectangle *MAPA);
void movimentarV(Vector2 *coisa);