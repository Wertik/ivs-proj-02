# Přispívání kódu

Jakmile master branch bude stabilní (hotová integrace UI a matematické knihovny), zásadně vytvářet pro nové prvky a bugfixy nové branche a mergovat přes pull request. Pull request si nechat schválit minimálně jedním člověkem.

# Komunikace

## Jazyk

Commit zprávy výhradně v angličtině. Delší komunikace, popisy, komunikace v Issues v češtině/slovenštině pro jednodušší komunikaci.

## Kontinuita

Pokud proběhne k Issue na githubu konverzace někde jinde (Discord, osobně), vždy závěr doplnit do GitHub issue.

# Code style

## Definice funkcí

Používat vždy camelCase, závorky nechat na stejném řádku jako definice funkce.
```c++
void myFunction() {
  // Code here
}
```

## Podmínky

Nepoužívat jednořádkové podmínky.
```c++
if (true) return 42;
```

Ideálně vždy použít blokové závorky a odřazení.
```c++
if (true) {
  return 42;
}
```

## Proměnné

Výhradně se držet camelCase a anglického jazyka.
```c++
int myVariable = 42;
```
