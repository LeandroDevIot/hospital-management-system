# Hospital Management System (HMS)

## Visão Geral do Projeto
O Hospital Management System é um monorepo concebido para integrar múltiplos serviços essenciais de gestão e atendimento hospitalar. O foco inicial deste projeto é o desenvolvimento de um Totem de Triagem Inteligente, projetado para emissão de senhas e otimização do fluxo de pacientes na receção.

O sistema é construído com uma arquitetura moderna, com o objetivo de futuramente incorporar uma API em Java Spring Boot (microsserviços) e interfaces web (React/Angular) para administração completa da unidade hospitalar.

---

## 🛠️ Tecnologias Utilizadas (Totem de Triagem)
* **Frontend UI:** Qt 6 e QML
* **Linguagem Principal:** C++ (Lógica de Controlo e Comunicação com Hardware)
* **Build System:** CMake
* **Integração de Hardware:** Impressão Térmica (via módulo `QtPrintSupport`)
* **Dispositivo Alvo:** X ZHANG POS-5802DD (Impressora Térmica 58mm)
* **Integração de SO:** Windows Spooler (Preparado para transição para Linux/CUPS via Raspberry Pi)

---

## 🚀 Funcionalidades Implementadas (MVP - Status Atual)

### 1. Interface de Utilizador (UI/QML)
* Ecrã principal interativo concebido para funcionamento em modo Kiosk (tátil).
* Teclado virtual integrado (`QtVirtualKeyboard`) com animações de transição suaves.
* Campo para introdução do CPF do paciente.
* Seleção de tipo de atendimento (Normal e Prioritário).

### 2. Controlo e Lógica (C++)
* Arquitetura de interface limpa entre QML e C++ através de `Q_INVOKABLE`.
* Verificação em tempo real da existência e ligação da impressora instalada no sistema operativo (driver Windows).

### 3. Integração de Hardware (Impressão Térmica)
* Implementação do módulo de impressão `QPrinter` com adaptação milimétrica para papel térmico de 58mm (remoção de margens).
* Utilização de `QPainter` para desenho e formatação gráfica do talão.
* Impressão bem sucedida com o seguinte layout gerado dinamicamente:
  * Cabeçalho ("HOSPITAL CENTRAL").
  * Tipo de Senha em destaque.
  * CPF associado.
  * Data e Hora do sistema.

---

## 🏗️ Estrutura do Monorepo
A organização do repositório reflete uma arquitetura escalável para os próximos módulos do sistema:

```text
hospital-management-system/
│
├── .gitignore               # Configurações de segurança e exclusão de builds
├── README.md                # Documentação central do ecossistema
│
├── totem-triagem-qt/        # (Ativo) Código-fonte do Totem em C++/Qt
│   ├── CMakeLists.txt
│   ├── main.cpp
│   ├── Main.qml
│   └── totemcontroller.cpp/h
│
├── backend-api/             # (Pendente) Microsserviços Java Spring Boot
└── frontend-web/            # (Pendente) Painel de Gestão em React/Angular
```

---

## 🔒 Segurança e Versionamento
* Repositório configurado com ligação SSH via chaves ED25519.
* `.gitignore` global implementado para prevenir o envio de ficheiros de build pesados do Qt (diretórios `build-*/`, CMake cache) e proteger o envio acidental de ficheiros `.env` e dependências locais de futuros módulos web e backend.

---

## 🔜 Próximos Passos (Roadmap)
1. **Lógica Sequencial:** Implementar geração sequencial de senhas (Ex: N-001, P-001).
2. **Persistência de Dados (Local):** Integrar base de dados SQLite no C++ para manter o histórico diário de senhas.
3. **Refinamento Visual:** Inclusão do logótipo na interface UI e impressão gráfica no talão.
4. **Comunicação de Rede:** Estruturar a classe C++ para envio do histórico via requisições HTTP REST para a futura API do hospital.

