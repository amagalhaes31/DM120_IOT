export default class Content {
    
    private temperatura: string = "0";
    private tempMin: string = "0";
    private tempMax: string = "0";
    private luminosidade: string = "0";
    private lumMin: string = "0";
    private lumMax: string = "0";



	constructor($temperatura: string , $tempMin: string , $tempMax: string , $luminosidade: string , $lumMin: string , $lumMax: string ) {
		this.temperatura = $temperatura;
		this.tempMin = $tempMin;
		this.tempMax = $tempMax;
		this.luminosidade = $luminosidade;
		this.lumMin = $lumMin;
		this.lumMax = $lumMax;
	}
    

    /**
     * Getter $temperatura
     * @return {string }
     */
	public get $temperatura(): string  {
		return this.temperatura;
	}

    /**
     * Getter $tempMin
     * @return {string }
     */
	public get $tempMin(): string  {
		return this.tempMin;
	}

    /**
     * Getter $tempMax
     * @return {string }
     */
	public get $tempMax(): string  {
		return this.tempMax;
	}

    /**
     * Getter $luminosidade
     * @return {string }
     */
	public get $luminosidade(): string  {
		return this.luminosidade;
	}

    /**
     * Getter $lumMin
     * @return {string }
     */
	public get $lumMin(): string  {
		return this.lumMin;
	}

    /**
     * Getter $lumMax
     * @return {string }
     */
	public get $lumMax(): string  {
		return this.lumMax;
	}

    /**
     * Setter $temperatura
     * @param {string } value
     */
	public set $temperatura(value: string ) {
		this.temperatura = value;
	}

    /**
     * Setter $tempMin
     * @param {string } value
     */
	public set $tempMin(value: string ) {
		this.tempMin = value;
	}

    /**
     * Setter $tempMax
     * @param {string } value
     */
	public set $tempMax(value: string ) {
		this.tempMax = value;
	}

    /**
     * Setter $luminosidade
     * @param {string } value
     */
	public set $luminosidade(value: string ) {
		this.luminosidade = value;
	}

    /**
     * Setter $lumMin
     * @param {string } value
     */
	public set $lumMin(value: string ) {
		this.lumMin = value;
	}

    /**
     * Setter $lumMax
     * @param {string } value
     */
	public set $lumMax(value: string ) {
		this.lumMax = value;
	}
    

   

}

