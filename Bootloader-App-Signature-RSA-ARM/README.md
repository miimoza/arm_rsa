# Signature-RSA-ARM

### Ecrire l'app PC qui envoie discute avec le bootloader pour flash
##### scripte python qui:
  - lance le flash (erase + start flash)
  - send packet de 4bytes (32bits)
  - arrete le flash (end flash)
  - erase la flash (erase flash)

### Ecrire l'app de gestionnaire de mot de passe
##### scripte python qui:
  - envoie un sha
  - demande une init de mdp
  - recup pubkey contre un mdp
  - recup privkey signed avec le sha envoyé au debut contre un mdp

### Wiring
  uart PC6 TX => RX COMPUTER
       PC7 RX => TX COMPUTER
       
  USB bootloader
