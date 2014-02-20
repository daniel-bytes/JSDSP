function audioCallback(inputs, outputs, numSamples, sampleRate, parameters) {
    for (var i = 0; i < numSamples; i++) {
        var value = Sawtooth.increment(sampleRate, parameters.frequency);

        for (var channel = 0; channel < outputs.length; channel++) {
            outputs[channel][i] = value;
        }
    }
}