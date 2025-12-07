clear;
clc;
close all;

%% ===============================
% CONFIGURAÇÕES GERAIS
% ===============================
numRuns = 100;

BASE_END = 10000;
BASE_LOG = 1000;
BASE_TAM_CONSULTA = 3;
BASE_POPULARIDADE = 0.5; % 0 = raras | 1 = populares

%% Vetores de variação
varEnderecos   = [1e3 3e3 1e4 3e4 1e5];
varLogradouros = [1e2 3e2 1e3 3e3 1e4];
varTamConsulta = [1 2 4 8 16];
varPopularidade = linspace(0,1,6);

%% ===============================
% FUNÇÕES DE CUSTO (modelo do seu C++)
% ===============================
custoConstrucao = @(E,L) ...
    E * log2(L+1) + ...
    L * log2(L+1);

custoConsulta = @(tam,pop,E) ...
    tam * log2(E+1) + ...
    pop * tam * sqrt(E); % popularidade impacta nº ocorrências

%% ===============================
% 1) VARIAÇÃO DO Nº DE ENDEREÇOS
% ===============================
tempoEnd = zeros(length(varEnderecos),1);

for i = 1:length(varEnderecos)
    tempos = zeros(numRuns,1);
    for r = 1:numRuns
        tic;
        custo = custoConstrucao(varEnderecos(i), BASE_LOG);
        pause(custo*1e-7 + rand()*1e-4);
        tempos(r) = toc;
    end
    tempoEnd(i) = mean(tempos);
end

%% ===============================
% 2) VARIAÇÃO DO Nº DE LOGRADOUROS
% ===============================
tempoLog = zeros(length(varLogradouros),1);

for i = 1:length(varLogradouros)
    tempos = zeros(numRuns,1);
    for r = 1:numRuns
        tic;
        custo = custoConstrucao(BASE_END, varLogradouros(i));
        pause(custo*1e-7 + rand()*1e-4);
        tempos(r) = toc;
    end
    tempoLog(i) = mean(tempos);
end

%% ===============================
% 3) VARIAÇÃO DO TAMANHO DA CONSULTA
% ===============================
tempoTam = zeros(length(varTamConsulta),1);

for i = 1:length(varTamConsulta)
    tempos = zeros(numRuns,1);
    for r = 1:numRuns
        tic;
        custo = custoConsulta(varTamConsulta(i), ...
                              BASE_POPULARIDADE, BASE_END);
        pause(custo*1e-6);
        tempos(r) = toc;
    end
    tempoTam(i) = mean(tempos);
end

%% ===============================
% 4) VARIAÇÃO DA POPULARIDADE
% ===============================
tempoPop = zeros(length(varPopularidade),1);

for i = 1:length(varPopularidade)
    tempos = zeros(numRuns,1);
    for r = 1:numRuns
        tic;
        custo = custoConsulta(BASE_TAM_CONSULTA, ...
                              varPopularidade(i), BASE_END);
        pause(custo*1e-6);
        tempos(r) = toc;
    end
    tempoPop(i) = mean(tempos);
end

%% ===============================
% GRÁFICOS
% ===============================

figure;
plot(varEnderecos, tempoEnd,'-o','LineWidth',2);
set(gca,'XScale','log','YScale','log');
xlabel('Número de Endereços');
ylabel('Tempo Médio (s)');
title('Impacto do Número de Endereços na Construção dos TADs');
grid on;

figure;
plot(varLogradouros, tempoLog,'-o','LineWidth',2);
set(gca,'XScale','log','YScale','log');
xlabel('Número de Logradouros');
ylabel('Tempo Médio (s)');
title('Impacto do Número de Logradouros na Construção dos TADs');
grid on;

figure;
plot(varTamConsulta, tempoTam,'-o','LineWidth',2);
xlabel('Tamanho da Consulta (palavras)');
ylabel('Tempo Médio (s)');
title('Impacto do Tamanho da Consulta');
grid on;

figure;
plot(varPopularidade, tempoPop,'-o','LineWidth',2);
xlabel('Popularidade das Palavras (0=rara, 1=popular)');
ylabel('Tempo Médio (s)');
title('Impacto da Popularidade da Consulta');
grid on;
