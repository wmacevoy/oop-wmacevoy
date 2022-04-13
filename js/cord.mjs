

export class DeviceObserver {
    deviceNotification(device, bulletin) {}
}
export class Device {
    constructor(ip) {
        this._ip = ip;
        this._observers = new Array();
        this._postponements = new Array();
        this._notifying = false;
    }

    removeObserver(observer) {
        if (this._notifying) {
            this._postponements.push(() => {this.removeObserver(observer)})
            return;
        }
        for (let i=0; i<this._observers.length; ++i) {
            if (this._observers[i] === observer) {
                this._observers.splice(i,1);
            }
        }
    }

    addObserver(observer) {
        if (this._notifying) {
            this._postponements.push(() => {this.addObserver(observer)})
            return;
        }
        this.removeObserver(observer);
        this._observers.push(observer);
    }

    _notify(bulletin) {
        this._notifying = true;
        for (let i=0; i<this._observers.length; ++i) {
            this._observers[i].deviceNotification(this,bulletin)
        }
        while (this._postponements.length > 0) {
            let postponements = this._postponements;
            this._postponements = new Array();
            postponements.forEach((postponement) => { postponement(); });
        }
        this._notifying = false;
    }

    api(json, callback) {
        console.log("sent " + JSON.stringify(json) + " to " + this._ip);
        setTimeout(()=>callback({ 'status': 200, 'response': json}), 100);
    }
}
export class Cord extends Device {
    constructor(ip, length, connector, capacity) {
        super(ip);
        this._length = null;
        this.length = length;
        this._connector = null;
        this.connector = connector;
        this._capacity = null;
        this.capacity = capacity; // this.set capacity(capacity);
    }

    get length() {
        return this._length;
    }

    set length(value) {
        if (value > 0.0) {
            this._length = value;
        } else {
            throw new RangeError("length must be positive");
        }
    }

    get connector() {
        return this._connector;
    }

    set connector(value) {
        if (value.startsWith("male ") || value.startsWith("female ")) {
            this._connector = value;
        } else {
            throw new RangeError("connector must be male or female");
        }
    }

    get capacity() {
        return this._capacity;
    }

    set capacity(value) {
        if (value > 0.0) {
            this._capacity = value;
        } else {
            throw new RangeError("capacity must be positive");
        }
    }

    // cord.opposite
    get opposite() {
        if (this._connector.startsWith("male")) {
            return "female" + this._connector.substring(4);
        } else {
            return "male" + this._connector.substring(6);
        }
    }

    compatible(equipment) {
        return this.capacity >= equipment.consumption
            && this.opposite == equipment.connector;
    }
}

// mixin
export class Fused extends Device {
    getFuseOk() {
        return this._fuseOk;
    }
    setFuseOk(value) {
        this._fuseOk = value;
    }
    trip() {
        this._fuseOk = false;
    }
    reset() {
        this._fuseOk = true;
    }
}

export class FusedCord extends Cord
{
    constructor(ip, length, connector, capacity, fuseOk,fuseType) {
        super(ip, length, connector, capacity);
        this._fuseOk = fuseOk;
        this._fuseType = fuseType;
    }
}
// https://blog.bitsrc.io/understanding-mixins-in-javascript-de5d3e02b466
function mixin(target, ...src) {
    for (let mixed of src) {
        for (var property of Object.getOwnPropertyNames(mixed.prototype)) {
            if (property != 'constructor') {
                target.prototype[property] = mixed.prototype[property]
            }
        }
    }
}

mixin(FusedCord,Fused);



let myCord = new FusedCord("127.0.0.1",10,"male 3 prong",20,true,"iso 3322");

myCord.reset();

console.log(myCord.getFuseOk());

console.log(`fused cord is fusedcord: ${myCord instanceof FusedCord}`);
console.log(`fused cord is cord: ${myCord instanceof Cord}`);
console.log(`fused cord is device: ${myCord instanceof Device}`);
console.log(`fused cord is fused: ${myCord instanceof Fused}`);


export class Equipment {
    constructor(consumption, connector, enabled) {
        this._consumption = consumption;
        this._connector = connector;
        this._enabled = enabled;
    }
}

export default {
    Cord,
    Fused,
    FusedCord,
    Equipment
}