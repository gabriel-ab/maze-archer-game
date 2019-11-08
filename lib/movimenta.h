#define VELOCIDADE_MAX 1
#define ACELERACAO 0.3
#define TAXA_ATRITO 0.015

void updateHitBoxes(Personagem *fulano);
void checkHitBoxes(Personagem *fulano, Rectangle *MAPA[]);

void aplicaInercia(Personagem *fulano);
void aplicaAtrito(Personagem *fulano, float taxa);

void movimentar(Personagem *fulano);
void movimentarV(Vector2 *coisa);
