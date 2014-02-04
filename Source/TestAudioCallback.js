var Sawtooth = {
    increment: function(sampleRate) {
        if (sampleRate !== this._sampleRate) {
            this._sampleRate = sampleRate;
            this._increment = (2.0 / this._sampleRate) * this._frequency;
        }

        this._value += this._increment;

        if (this._value >= 1.0) {
            this._value -= 2.0;
        }

        return this._value;
    },

    _frequency: parseFloat(200.0),
    _sampleRate: parseFloat(0.0),
    _increment: parseFloat(0.0),
    _value: parseFloat(0.0)
}

function audioInit(sampleRate) {

}

function audioCallback(inputs, outputs, numSamples, sampleRate) {
    for (var i = 0; i < numSamples; i++) {
        var value = Sawtooth.increment(sampleRate);

        for (var channel = 0; channel < outputs.length; channel++) {
            outputs[channel][i] = value;
        }
    }
}