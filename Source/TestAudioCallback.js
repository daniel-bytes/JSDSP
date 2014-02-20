var Sawtooth = {
    increment: function(sampleRate, freq) {
        //if (sampleRate !== this._sampleRate || freq !== this._frequency) {
            this._sampleRate = sampleRate;
            this._frequency = freq;
            this._increment = (2.0 / this._sampleRate) * this._frequency;
        //}

        this._value += this._increment;

        if (this._value >= 1.0) {
            this._value -= 2.0;
        }

        return this._value > .5 ? 1.0 : -1.0;
    },

    _frequency: parseFloat(100.0),
    _sampleRate: parseFloat(44100.0),
    _increment: parseFloat(0.0),
    _value: parseFloat(0.0)
}

function audioInit(sampleRate) {

}

function audioCallback(inputs, outputs, numSamples, sampleRate, parameters) {
    for (var i = 0; i < numSamples; i++) {
        var value = Sawtooth.increment(sampleRate, parameters.frequency);

        for (var channel = 0; channel < outputs.length; channel++) {
            outputs[channel][i] = value;
        }
    }
}