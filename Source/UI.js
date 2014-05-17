var frequencyKnob = document.getElementById('frequency');
log("frequencyKnob:", frequencyKnob);
log('Parameter:', frequencyKnob.parameter);

frequencyKnob.parameter = 200;
log('Parameter:', frequencyKnob.parameter);

frequencyKnob.parameterChanged = function(value) {
    log('parameterChanged', value);
}