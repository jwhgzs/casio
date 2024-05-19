let str = ''

function go(i) {
    if (i > 9) return
    if (str)
        str += `\nElse `
    str += `If U=${i}`
    str += `\nThen "${i}"+Str 1->Str 1`
    go(i + 1)
    str += `\nIfEnd`
}

go(0)
console.log(str)
