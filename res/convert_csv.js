const fs = require('fs')

const alp = 'abcdefghijklmnopqrstuvwxyz'.split('')
function numeric(str) {
    let res = ''
    for (let v of str) {
        let i = alp.indexOf(v.toLowerCase()) + 1
        i = i < 10 ? '3' + i : '' + i
        res += i
    }
    return res
}

let lines = fs.readFileSync('./ori.csv', 'utf8').split('\n')
let res = ''
let i = 0
for (let k in lines) {
    let v = lines[k].replace(/^\s/g, '').replace(/\s$/g, '')
    let w = v.split(',')
    if (w[0].match(/^[a-zA-Z]+$/) && w[0].length == 6)
        res += numeric(w[0]) + '\n'
    i ++
}
fs.writeFileSync('./words.csv', res)
