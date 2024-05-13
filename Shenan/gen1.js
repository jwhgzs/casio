const alp = 'abcdefghijklmnopqrstuvwxyz'
let str = ''

function go(i) {
    if (! alp[i]) return
    let v = alp[i]
    if (str)
        str += `\nElse `
    str += `If List 2[J]=${ i + 1 < 10 ? '3' + (i + 1) : '' + (i + 1) }`
    str += `\nThen Str 1+"${v}"->Str 1`
    go(i + 1)
    str += `\nIfEnd`
}

go(0)
console.log(str)
