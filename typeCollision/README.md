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
