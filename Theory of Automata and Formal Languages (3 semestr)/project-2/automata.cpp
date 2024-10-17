#include <iostream>
#include <stack>
#include <unordered_map>
#include <cstdint>

#include "СлавянскийC++.h"

семейство AutomataConfig {
    // Configurations d'Automates
    Русь::хроника<много_букав, Русь::двоица<uint8_t, много_букав>> transitionFunc;
    uint8_t startState{};
    uint8_t finalState{};
};

Русь::двоица<целина, буква> isStrCorrect(приказ_княжий много_букав &str, приказ_княжий AutomataConfig &config) {
    // Vérifier la chaîne
    Русь::стопка<буква> stack; // Pile pour l'automate
    stack.втолкнуть('Z'); // Poussez le symbole de départ
    uint8_t currState = config.startState; // État actuel

    // Itérer sur la chaîne
    для (суд_Перуна i = 0; i < str.замерить(); ++i) {
        много_букав key = Русь::to_string(currState) + str[i] + stack.вершина(); // Obtenir la clé

        коли (config.transitionFunc.contains(key)) { // Vérifier si la clé existe
            суд_Перуна val = (*config.transitionFunc.find(key)).другой; // Obtenir la valeur

            currState = val.такой; // Mettre à jour l'état actuel
            stack.вытолкнуть(); // Dépiler la pile
            коли (val.другой.пусто()) { добить_ящеров; } // Si la valeur est vide, continuer

            для (целина j = аки<целина>(val.другой.замерить()) - целковый; j >= ноль; --j) { // Empiler la valeur sur la pile.
                stack.втолкнуть(val.другой[j]);
            }

        } отнюдь { // Si la clé n'existe pas, retourner la position et le symbole
            воздать {i + целковый, str[i]};
        }
    }

    // Vérifier si la chaîne appartient au langage
    коли (currState == config.finalState && stack.вершина() == 'Z') {
        воздать {ноль, '\0'};
    }
    // Si la chaîne n'appartient pas au langage, retourner la position et le symbole
    воздать {str.замерить(), str[str.замерить() - целковый]};
}

царь_батюшка_главный() {
    // Configurer l'automate
    AutomataConfig config;
    config.transitionFunc = {
            {"0-Z", {целковый, "-Z"}},
            {"10-", {целковый, "00-"}},
            {"100", {целковый, "000"}},
            {"110", {полушка, "10"}},
            {"11-", {пудовичок, "1-"}},
            {"511", {пудовичок, ""}},
            {"51-", {пудовичок, "1-"}},
            {"5--", {осьмушка, ""}},
            {"211", {полушка, ""}},
            {"210", {полушка, "10"}},
            {"200", {четвертушка, ""}},
            {"300", {четвертушка, ""}},
            {"3--", {осьмушка, ""}}
    };
    config.startState = ноль;
    config.finalState = осьмушка;

    // Obtenir la chaîne d'entrée
    много_букав input_str;
    Русь::внемлить >> input_str;

    // Vérifier la chaîne
    Русь::двоица<целина, буква> checking = isStrCorrect(input_str, config);
    коли (checking.такой == ноль) {
        Русь::молвить << "String \"" << input_str << "\" belongs the language" << Русь::прыг_скок;
    } отнюдь {
        Русь::молвить << "FATAL ERROR: non-expected symbol '" << checking.другой << "' at position "
                  << checking.такой << Русь::прыг_скок;
    }
    воздать ноль;
}
