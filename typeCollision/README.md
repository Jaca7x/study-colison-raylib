# AABB (Axis-Aligned Bounding Box)
Explicando com simplicidade:
É um retângulo que envolve um objeto sem rotacionar, ou seja, sempre alinhado aos eixos X e Y. Imagine uma caixa invisível ao redor de um personagem, obstáculo ou item. Se duas dessas caixas se sobrepõem, dizemos que houve colisão AABB.

Exemplo visual
```
+----------+          +----------+
|  ret1    |          | ret2     |
|          |          |          |
+----------+          +----------+

Movendo `ret1` para a direita até encostar em `ret2`:
Quando eles se sobrepõem, a função retorna true.
```
Vantagens: <br/>
1 - Simples de aplicar<br/>
2 - Rápido (só 4 comparações)<br/>

Desvantagens: <br/>
1 - Não funciona com objetos rotacionados<br/>
2 - Pode ser impreciso com formas complexas (tipo triângulos ou sprites arredondados)<br/>
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
# OBB (Oriented Bounding Box)
É como um retângulo rotacionado que envolve um objeto. Diferente da AABB (Axis-Aligned Bounding Box), ele pode estar inclinado ou girar, pois não precisa estar alinhado com os eixos X e Y.
```
Com rotação (OBB)
  /-----/
 /     /
/-----/
```
**Como detectar colisão entre dois OBBs**<br/>
**SAT - Teorema do Eixo Separador**<br/>
Ideia: Se dois polígonos convexos não colidem, sempre existe um eixo no qual as projeções deles não se sobrepõem.<br/>
Se todas as projeções em todos os eixos se sobrepõem, então eles estão colidindo.<br/>

**Como aplicar no OBB:**<br/>
- Calcular os 4 vértices do OBB (usando center, halfSize e rotation).<br/>

**Obter os eixos de projeção:**<br/>

- Cada lado do retângulo gera um eixo perpendicular.<br/>

- São 2 do primeiro OBB + 2 do segundo → 4 eixos.<br/>

**Para cada eixo:**<br/>

- Projetar os vértices dos dois OBBs nesse eixo.<br/>

- Ver se as projeções se sobrepõem.<br/>

- Se houver qualquer separação, não há colisão.<br/>

- Se nenhuma separação for encontrada, então há colisão.<br/>

**Código essencial:** 
```C
typedef struct {
    Vector2 center;
    Vector2 halfSize;
    float rotation;
} OBB;

void GetOBBVertices(OBB obb, Vector2 out[4]);
bool CheckOBBCollision(OBB a, OBB b);
```

**Onde OBB é usado?**<br/>
- Jogos com carros, aviões, navios (movem-se e giram).<br/>

- Plataformas inclinadas.<br/>

- Itens ou armas com rotação (espadas, shurikens).<br/>

- Qualquer jogo que precise de colisão mais precisa que AABB.<br/>


