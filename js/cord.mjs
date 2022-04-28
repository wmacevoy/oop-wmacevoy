

export class DeviceFactory {
    /* Device */ build(/* json */ what);
}

class DB {
    constructor() {
        this._connected = null;
    }
    /* DB */ connect() {
        if (this._connected) return this._connected;
        ...
    }

}

export const db = new DB();
db.connect(); // lazy
export class DeviceObserver {
    deviceNotification(device, bulletin) {}
}

export class Logger extends DeviceObserver {
    constructor() {
        super();
        this._deviceNotifications=new Array();
    }
    deviceNotification(device, bulletin) {
        this._deviceNotifications.push({'device': device, 'bulletin': bulletin});
        console.log("device",device,"bulletin",bulletin);
    }
}

export const logger = new Logger();

export class Device extends DeviceObserver {
    constructor(ip) {
        super();
        this._ip = ip;
        this._observers = new Array();
        this._postponements = new Array();
        this._notifying = false;
        this.addObserver(logger);
    }

    toString() {
        return `${this._ip}`
    }

    _removeObserver(observer) {
        for (let i=0; i<this._observers.length; ++i) {
            if (this._observers[i] === observer) {
                this._observers.splice(i,1);
            }
        }
    }

    removeObserver(observer) {
        if (this._notifying) {
            const me = this;
            this._postponements.push(() => {me._removeObserver(observer)})
        } else {
            this._removeObserver(observer);
        }
    }

    _addObserver(observer) {
        this._removeObserver(observer);
        this._observers.push(observer);
    }

    addObserver(observer) {
        if (this._notifying) {
            const me = this;
            this._postponements.push(() => {me._addObserver(observer)})
        } else {
            this._addObserver(observer);
        }
    }

    _notify(bulletin) {
        this._notifying = true;
        this._observers.forEach((observer)=>observer.deviceNotification(this,bulletin));
        for (;;) {
            const postponements = this._postponements;
            if (postponements.length == 0) break;
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
        this._powersDevice = null;
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

    unplug() {
        if (this._powersDevice != null) {
            this._notify({'action':'unplug', 'target':this._powersDevice});
            this._powersDevice = null;
        }
    }

    power(device) {
        if (this._powersDevice !== device) {
            this.unplug();
            this._notify({'action':'will-power','target':device});
            this._powersDevice = device;
            this._notify({'action':'power','target':device});
        }
    }


}

// mixin
export class Fused extends Device {
    constructor(ip) {
        super(ip);
    }
    getFuseOk() {
        return this._fuseOk;
    }
    setFuseOk(value) {
        if (value != this._fuseOk) {
            this._notify({'action':'will-set-fuse-ok','target':value});
            this._fuseOk = value;
            this._notify({'action':'set-fuse-ok','target':value});
        }
    }
    trip() {
        this.setFuseOk(false);
    }
    reset() {
        this.setFuseOk(true);
    }
}

export class FusedCord extends Cord
{
    constructor(ip, length, connector, capacity, fuseOk,fuseType) {
        super(ip, length, connector, capacity);
        this._fuseOk = fuseOk;
        this._fuseType = fuseType;
        this._wasPluggedTo = null;
        this.addObserver(this);
    }

    deviceNotification(device, bulletin) {
        if (this._powersDevice != null && device === this &&
            bulletin['action'] == 'will-set-fuse-ok' && 
            bulletin['target'] == false) {
                this._wasPluggedTo = this._powersDevice;
                this.unplug();
        }
        
        if (this._wasPluggedTo != null && device === this &&
            bulletin['action'] == 'will-set-fuse-ok' && 
            bulletin['target'] == true) {
                power(this._wasPluggedTo);
                this._wasPluggedTo = null;
        }
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


export class Equipment extends Device {
    constructor(ip, consumption, connector, enabled) {
        super(ip);
        this._consumption = consumption;
        this._connector = connector;
        this._enabled = enabled;
    }
    deviceNotification(device, bulletin) {
        console.log("got notification from " + device + ": " + JSON.stringify(bulletin));
    }

}

export default {
    Cord,
    Fused,
    FusedCord,
    Equipment
}