const mesclarCores = (cor1, cor2) => {
  // Combinações com vermelho
  if (cor1 == "vermelho") {
    switch (cor2) {
      case "verde":
        return "amarelo";
      case "azul":
        return "magenta";
    }
  }
  if (cor2 == "vermelho") {
    switch (cor1) {
      case "verde":
        return "amarelo";
      case "azul":
        return "magenta";
    }
  }

  // Combinações com verde
  if (cor1 == "verde") {
    switch (cor2) {
      case "vermelho":
        return "amarelo";
        break;
      case "azul":
        return "ciano";
        break
    }
  }
  if (cor2 == "verde") {
    switch (cor1) {
      case "vermelho":
        return "amarelo";
        break;
      case "azul":
        return "ciano";
        break
    }
  }

  // Combinações com azul
  if (cor1 == "azul") {
    switch (cor2) {
      case "vermelho":
        return "magenta";
        break;
      case "verde":
        return "ciano";
        break;
    }
  }
  if (cor2 == "azul") {
    switch (cor1) {
      case "vermelho":
        return "magenta";
        break;
      case "verde":
        return "ciano";
        break;
    }
  }
};

const get_results = async () => {
  const res = await fetch('http://recnplay2023.pythonanywhere.com/resultados').then((res) => res.json());
  
  var ultimaMaisVotada;
  var ultimaSegundaMaisVotada;
  var qntdVermelho = res.vermelho;
  var qntdAzul = res.azul;
  var qntdVerde = res.verde;

  console.log(res);

  if (qntdVermelho >= qntdVerde && qntdVermelho >= qntdAzul) {
    ultimaMaisVotada = "vermelho";

    if (qntdVerde > qntdAzul) {
      ultimaSegundaMaisVotada = "verde";
    } else {
      ultimaSegundaMaisVotada = "azul";
    }
  } else if (qntdVerde >= qntdVermelho && qntdVerde >= qntdAzul) {
    ultimaMaisVotada = "verde";

    if (qntdVermelho > qntdAzul) {
      ultimaSegundaMaisVotada = "vermelho"
    } else {
      ultimaSegundaMaisVotada = "azul";
    }
  } else if (qntdAzul >= qntdVermelho && qntdAzul >= qntdVerde) {
    ultimaMaisVotada = "azul";
        
    if (qntdVermelho > qntdVerde) {
      ultimaSegundaMaisVotada = "vermelho";
    } else {
      ultimaSegundaMaisVotada = "verde";
    }
  }

  console.log(ultimaMaisVotada);
  console.log(ultimaSegundaMaisVotada);
  console.log(mesclarCores(ultimaMaisVotada, ultimaSegundaMaisVotada));
}

get_results();
