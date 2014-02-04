var value = parseFloat(0);
var increment = (2.0 / 44100.0) * 200.0;

function audioCallback(inputs, outputs, numSamples) {
    for (var i = 0; i < numSamples; i++) {
        value += increment;

        if (value >= 1.0) {
            value -= 2.0;
        }

        for (var channel = 0; channel < outputs.length; channel++) {
            outputs[channel][i] = value;
        }
    }
}