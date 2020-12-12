import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';
import { DweetService } from 'src/app/services/dweet.service';
import Dweet from 'src/models/Dweet';

@Component({
  selector: 'app-luminosidade',
  templateUrl: './luminosidade.page.html',
  styleUrls: ['./luminosidade.page.scss'],
})
export class LuminosidadePage implements OnInit {

  private dweet: Dweet
  private isLoading: boolean = true;
  private time: any;
  private dataPlot: Array<any>

  options: Object;

  constructor(public router: Router, private dweetService: DweetService) { 
    this.time = setInterval(() => {this.getLastDweets()}, 3000)
  }

  ngOnInit() {
    this.getLastDweets();
  }

  ngOnDestroy(){
    clearInterval(this.time)
  }

  private getLastDweets(){
    this.dataPlot = []
    this.dweetService.loadLastDweets().subscribe(
      data => {
        this.preencherDweet(data)
      }, 
      err => {
        console.log("Erro: ", err)
      },
      () => this.isLoading = false
    )
  }

  private preencherDweet(data: any){
    this.dweet = this.dweetService.preencherDweet(data); 
    this.loadDataForPlot(this.dweet)
    this.plotChart();
  }

  private loadDataForPlot(dweet: Dweet){
    for(let _with of dweet.with){
      let epoch = new Date(_with.created).getTime()
      this.dataPlot.push([epoch, _with.content.$luminosidade])
    }
  }

  private plotChart(){
    this.options = {
      xAxis: {
        type: 'datetime'
      },
      yAxis: {
        labels: {
          formatter: function(){
            return this.value + "Lux";
          }
        },
      },
      title: { text: 'Luminosidade '},
        series: [{
          name: 'luminosidade',
          data: this.dataPlot.reverse(),
          pointInterval: 60 * 60
        }]
    };
  }

  goBack(){
    this.router.navigate(['home'])
  }

}