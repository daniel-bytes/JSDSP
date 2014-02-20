var Sawtooth = {
    increment: function(sampleRate, freq, gain, lfoFreq) {
        if (sampleRate !== this._sampleRate || freq !== this._frequency) {
            this._sampleRate = sampleRate;
            this._frequency = freq;
            this._increment = (2.0 / this._sampleRate) * this._frequency;
        }

        this._value += this._increment;

        if (this._value >= 1.0) {
            this._value -= 2.0;
        }

        var lfo = LFO.increment(sampleRate, lfoFreq);
        return (this._value > .5 ? 1.0 : -1.0) * (gain * gain) * lfo;
    },

    _frequency: parseFloat(100.0),
    _sampleRate: parseFloat(44100.0),
    _increment: parseFloat(0.0),
    _value: parseFloat(0.0)
};

var LFO = {
    increment: function(sampleRate, freq) {
        if (sampleRate !== this._sampleRate || freq !== this._frequency) {
            this._sampleRate = sampleRate;
            this._frequency = freq;
            this._increment = (1.0 / this._sampleRate) * this._frequency;
        }

        this._value += this._increment;

        if (this._value >= 1.0) {
            this._value -= 1.0;
        }

        return this._value;
    },

    _frequency: parseFloat(1.0),
    _sampleRate: parseFloat(44100.0),
    _increment: parseFloat(0.0),
    _value: parseFloat(0.0)
};