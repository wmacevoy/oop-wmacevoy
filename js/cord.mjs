
export class Cord {
    constructor(length, connector, capacity) {
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

export class Equipment {
    constructor(consumption, connector, enabled) {
        this._consumption = consumption;
        this._connector = connector;
        this._enabled = enabled;
    }
}

export default {
    Cord,
    Equipment
}